// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "ItemBuffs.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "CactusGame/CactusGameCharacter.h"
#include "Kismet/GameplayStatics.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Mesh"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	RootComponent = Mesh;
	Box->SetupAttachment(Mesh);
	AmmoMesh->SetupAttachment(Mesh);
	
}

void ABaseWeapon::ForceBroadcastAmmo()
{
	OnAmmoChanged.Broadcast(CurrentMagazine,MaxMagazine);
}

void ABaseWeapon::ConsumeAmmo(int Amount)
{
	CurrentMagazine = FMath::Clamp(CurrentMagazine - Amount, 0, MaxMagazine);
	OnAmmoChanged.Broadcast(CurrentMagazine,MaxMagazine);
}

void ABaseWeapon::Reload()
{
	if (CurrentMagazine < MaxMagazine || CurrentMagazine == 0)
	{
		CurrentMagazine = MaxMagazine;
		OnAmmoChanged.Broadcast(CurrentMagazine,MaxMagazine);
	}
}

void ABaseWeapon::Fire()
{
	const float FinalDamage = CalculateDamage() + Damage;
	AActor* WeaponOwner = GetOwner();
	if (ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(WeaponOwner))
	{
		UCameraComponent* Camera = Character->GetFirstPersonCameraComponent();
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + Camera->GetForwardVector() * Range;
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Character);
		QueryParams.AddIgnoredActor(this);
		FHitResult HitResult;
		
		if (CurrentMagazine > 0)
        	{
        		ConsumeAmmo(1);
				ShotCooldown();
				bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
				DrawDebugLine(GetWorld(), Start, bHit ? HitResult.Location : End, FColor::Red, false, 1.f, 0, 1.f);
				UE_LOG(LogTemp, Warning, TEXT("Current Magazine: %d, Dmg Per Shot: %f"), CurrentMagazine, FinalDamage);
		

				if (bHit)
				{
					AActor* HitActor = HitResult.GetActor();
					if (HitActor)
					{
						UGameplayStatics::ApplyDamage(HitActor, FinalDamage, Character->GetInstigatorController(), this, nullptr);
					}
				}
				if (CurrentMagazine == 0)
				{
					Reload();
				}
        	}
		
	}
	
}

void ABaseWeapon::StartFiring()
{
	if (!CanFire()) return;
	Fire(); // fire once immediately
	
	if (bAutomatic && FireRate > 0.f)
	{
		const float interval = 1.f / FireRate;
		GetWorldTimerManager().SetTimer(FireTimer, this, &ABaseWeapon::Fire, interval, true, interval);
	}
}

void ABaseWeapon::StopFiring()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}

bool ABaseWeapon::CanFire() const
{
	const UWorld* World = GetWorld();
	if (!World) return false;

	const double Now = World->GetTimeSeconds();

	const bool bHasAmmo = (CurrentMagazine > 0);
	const bool bCooldownDone = (Now >= NextShot);
	const bool bReady = bHasAmmo && bCooldownDone && !bIsReloading;
	
	return bReady;
	
}

void ABaseWeapon::ShotCooldown()
{
	if (UWorld* World = GetWorld())
	{
		const double Now = World->GetTimeSeconds();
		double Interval;
		if (FireRate > 0.f)
		{
			Interval = 1.f / FireRate;
		}
		else
		{
			Interval = 0.f;
		}
		
		NextShot = Now + Interval;
	}
}

void ABaseWeapon::ApplyWeaponBuff(UItemBuffs* Buff)
{
	if (Buff)
	{
		if (Buff->DMGModifier != 1)
		{
			Damage *= Buff->DMGModifier;
		}
	}
}

float ABaseWeapon::CalculateDamage()
{
	if (ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(GetOwner()))
	{
		return Damage * Character->InventoryComponent->DmgMultiplier;
		
	}
	return Damage;
}

void ABaseWeapon::DropWeapon(AActor* OwnerActor, float Distance)
{
	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
		return;
	}
	ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(OwnerActor);
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not a character"));
		return;
	}
	else
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		FVector Start = Character->GetActorLocation();
		FVector Forward = Character->GetActorForwardVector();
		FVector DropLocation = Start + Forward * Distance;
		SetActorLocation(DropLocation,false);
		EnablePhysics(Forward * 100.f + FVector(0,0,100));
		SetOwner(nullptr);
	}
}
	


void ABaseWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(OtherActor);
	DisablePhysics();
	if (Character)
	{
		if (!Character->CurrentWeapon)
		{
			Character->CurrentWeapon = this;
			SetOwner(Character);
			if (Character && Character->GetMesh1P())
			{
				AttachToComponent(Character->GetMesh1P(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon_rSocket"));
				AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				AmmoMesh->SetGenerateOverlapEvents(false);
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Mesh->SetGenerateOverlapEvents(false);
				Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Box->SetGenerateOverlapEvents(false);
			}
		}
		else if (!Character->SecondaryWeapon)
		{
			Character->SecondaryWeapon = this;
			SetOwner(Character);
			UE_LOG(LogTemp,Warning,TEXT("Secondary is %s"),*GetClass()->GetName());
			if (Character && Character->GetMesh1P())
			{
				AttachToComponent(Character->GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("SecondaryWeapon"));
				AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				AmmoMesh->SetGenerateOverlapEvents(false);
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Mesh->SetGenerateOverlapEvents(false);
				Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Box->SetGenerateOverlapEvents(false);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Already holding two weapons; ignoring pickup for %s"), *GetName());
}

void ABaseWeapon::BeginPlay()
{
	if (CurrentMagazine == 0)
		CurrentMagazine = MaxMagazine;
	Super::BeginPlay();
	
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::DisablePhysics()
{
	if (UPrimitiveComponent* RootPrimitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		RootPrimitive->SetSimulatePhysics(false);
		RootPrimitive->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RootPrimitive->SetNotifyRigidBodyCollision(false);
	}
	if (Box && Mesh)
	{
		AmmoMesh->SetGenerateOverlapEvents(false);
		Mesh->SetGenerateOverlapEvents(false);
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Box->SetGenerateOverlapEvents(false);
	}
}

void ABaseWeapon::EnablePhysics(const FVector& Impulse)
{
	
	if (UPrimitiveComponent* RootPrimitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		RootPrimitive->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		RootPrimitive->SetSimulatePhysics(true);
		RootPrimitive->SetNotifyRigidBodyCollision(false);
		RootPrimitive->AddImpulse(Impulse, NAME_None, true);
	}
	if (Box && Mesh)
	{
		AmmoMesh->SetGenerateOverlapEvents(false);
		Mesh->SetGenerateOverlapEvents(false);
		Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Box->SetGenerateOverlapEvents(true);
	}
}

