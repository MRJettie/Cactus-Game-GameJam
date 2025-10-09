// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "CactusGame/CactusGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	RootComponent = Mesh;
	Box->SetupAttachment(Mesh);
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
	AActor* WeaponOwner = GetOwner();
	if (ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(WeaponOwner))
	{
		UCameraComponent* Camera = Character->GetFirstPersonCameraComponent();
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + Camera->GetForwardVector() * Range;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Owner);
		FHitResult HitResult;
		
		if (CurrentMagazine > 0)
        	{
        		ConsumeAmmo(1);
				bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
				DrawDebugLine(GetWorld(), Start, bHit ? HitResult.Location : End, FColor::Red, false, 1.f, 0, 1.f);
				UE_LOG(LogTemp, Warning, TEXT("Current Magazine: %d"), CurrentMagazine)

				if (bHit)
				{
					AActor* HitActor = HitResult.GetActor();
					if (HitActor)
					{
						UGameplayStatics::ApplyDamage(HitActor, Damage, Owner->GetInstigatorController(), this, nullptr);
						UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s for %f damage!"), *HitActor->GetName(), Damage);
					}
				}
				if (CurrentMagazine == 0)
				{
					Reload();
				}
        	}
		
	}
	
}

void ABaseWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(OtherActor);
	if (Character)
	{
		if (!Character->CurrentWeapon)
		{
			Character->CurrentWeapon = this;
			SetOwner(Character);
			if (Character && Character->GetMesh1P())
			{
				AttachToComponent(Character->GetMesh1P(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon_rSocket"));
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Mesh->SetGenerateOverlapEvents(false);
				Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Box->SetGenerateOverlapEvents(false);
			}
		}
		if (!Character->SecondaryWeapon)
		{
			Character->SecondaryWeapon = this;
			SetOwner(Character);
			UE_LOG(LogTemp,Warning,TEXT("Secondary is %s"),*GetClass()->GetName());
			if (Character && Character->GetMesh1P())
			{
				AttachToComponent(Character->GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("SecondaryWeapon"));
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Mesh->SetGenerateOverlapEvents(false);
				Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Box->SetGenerateOverlapEvents(false);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Already holding two weapons; ignoring pickup for %s"), *GetName());
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	if (CurrentMagazine == 0)
		CurrentMagazine = MaxMagazine;
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

