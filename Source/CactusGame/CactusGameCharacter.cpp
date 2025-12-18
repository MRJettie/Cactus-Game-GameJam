// Copyright Epic Games, Inc. All Rights Reserved.

#include "CactusGameCharacter.h"

#include "BaseWeapon.h"
#include "Public/HealthComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ACactusGameCharacter::ACactusGameCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}


void ACactusGameCharacter::WeaponSwap(const FInputActionValue& Value)
{
	if (CurrentWeapon&&SecondaryWeapon)
	{
		CurrentWeapon->StopFiring();
		SecondaryWeapon->StopFiring();
		ABaseWeapon* Temp = CurrentWeapon;
		CurrentWeapon=SecondaryWeapon;
		CurrentWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("weapon_rSocket"));
		SecondaryWeapon=Temp;
		SecondaryWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("SecondaryWeapon"));
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->SetInstigator(this);
		CallWidget_ConnectToWeapon(CurrentWeapon);
		
	}
	
}

void ACactusGameCharacter::WeaponDrop(const FInputActionValue& Value)
{
	if (CurrentWeapon && SecondaryWeapon)
	{
		CurrentWeapon->StopFiring();
		ABaseWeapon* Temp = CurrentWeapon;
		CurrentWeapon = SecondaryWeapon;
		SecondaryWeapon = nullptr;
		bOneWeaponDrop = true;
		CurrentWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("weapon_rSocket"));
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->SetInstigator(this);
		CallWidget_ConnectToWeapon(CurrentWeapon);
		Temp->DropWeapon(this,200);
	}
}

void ACactusGameCharacter::Reload(const FInputActionValue& Value)
{
	CurrentWeapon->Reload();
}

void ACactusGameCharacter::CallWidget_ConnectToWeapon(ABaseWeapon* Weapon)
{
	if (!WeaponHud) return;

	static const FName FuncName(TEXT("ConnectToWeapon")); 
	if (UFunction* Fn = WeaponHud->FindFunction(FuncName))
	{
		struct FParams { ABaseWeapon* Weapon; } Params{ Weapon };
		WeaponHud->ProcessEvent(Fn, &Params);
	}
}

void ACactusGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (StartingWeapon)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(StartingWeapon,SpawnParams);
		CurrentWeapon->CurrentMagazine = CurrentWeapon->MaxMagazine;
		if (CurrentWeapon)
		{
			SecondaryWeapon = nullptr;
			bEquipped = true;
			CurrentWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetIncludingScale,FName(TEXT("weapon_rSocket")));
			UE_LOG(LogTemp, Warning, TEXT("Weapon Spawned"));
			CurrentWeapon->Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CurrentWeapon->AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CallWidget_ConnectToWeapon(CurrentWeapon);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StarterWeaponClass is NULL — set it in BP defaults!"));
	}
	
}

float ACactusGameCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	if (HealthComponent)
	{
		float ReducedAmount = HealthComponent->DamageReduction(DamageAmount);
		HealthComponent->ApplyDamage(ReducedAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ACactusGameCharacter::FireWeaponStart(const FInputActionValue& Value)
{
	if (CurrentWeapon && bEquipped)
	{
			CurrentWeapon->StartFiring();
		
	}
}

void ACactusGameCharacter::FireWeaponEnd(const FInputActionValue& Value)
{
	if (CurrentWeapon)
	{
		if (CurrentWeapon->Damage == CurrentWeapon->Damage)
		{
			CurrentWeapon->StopFiring();
		}

	}
}

/*				Input			*/
void ACactusGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::Look);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::CheckInventory);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ACactusGameCharacter::FireWeaponStart);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Canceled,  this, &ACactusGameCharacter::FireWeaponEnd);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ACactusGameCharacter::FireWeaponEnd);
		EnhancedInputComponent->BindAction(WeaponSwitch,ETriggerEvent::Completed, this, &ACactusGameCharacter::WeaponSwap);
		EnhancedInputComponent->BindAction(DropItem, ETriggerEvent::Completed, this, &ACactusGameCharacter::WeaponDrop);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::Reload);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ACactusGameCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACactusGameCharacter::Look(const FInputActionValue& Value)
{
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACactusGameCharacter::CheckInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory Check"));
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is not NULL"));	
	}
	InventoryComponent->CheckWater();
}
