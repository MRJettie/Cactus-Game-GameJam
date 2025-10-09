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
#include "SNegativeActionButton.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACactusGameCharacter

ACactusGameCharacter::ACactusGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//Attaches Inventory Component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}


void ACactusGameCharacter::WeaponSwap()
{
	if (CurrentWeapon&&SecondaryWeapon)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		SecondaryWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		ABaseWeapon* Temp = CurrentWeapon;
		CurrentWeapon=SecondaryWeapon;
		CurrentWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("wepaon_rSocket"));
		SecondaryWeapon=Temp;
		SecondaryWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("SecondaryWeapon"));
		
	}
}

void ACactusGameCharacter::BeginPlay()
{
	// Call the base class  
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
			bEquipped = true;
			CurrentWeapon->AttachToComponent(GetMesh1P(),FAttachmentTransformRules::SnapToTargetIncludingScale,FName(TEXT("weapon_rSocket")));
			UE_LOG(LogTemp, Warning, TEXT("Weapon Spawned"));
			CurrentWeapon->Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
		HealthComponent->SimpleDamage(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ACactusGameCharacter::FireWeapon()
{
	if (CurrentWeapon && bEquipped)
	{
		CurrentWeapon->Fire();
		
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ACactusGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::Look);

		//Inventory Check
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::CheckInventory);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ACactusGameCharacter::FireWeapon);

		EnhancedInputComponent->BindAction(WeaponSwitch,ETriggerEvent::Triggered, this, &ACactusGameCharacter::WeaponSwap);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ACactusGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACactusGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
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
