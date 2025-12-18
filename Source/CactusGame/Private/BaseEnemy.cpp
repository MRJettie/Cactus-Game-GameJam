// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "HealthComponent.h"
#include "CactusGame/CactusGameCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetGenerateOverlapEvents(false);

}

void ABaseEnemy::Patrol()
{
	FVector Location = GetActorLocation();
}

void ABaseEnemy::Attack()
{
	FVector StartingLocation = GetActorLocation();
	FVector Direction = GetActorForwardVector();
	
}



float ABaseEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (HealthComponent)
	{
		float ReducedAmount = HealthComponent->DamageReduction(DamageAmount);
		HealthComponent->ApplyDamage(ReducedAmount);
		if (ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(EventInstigator->GetPawn()))
		{
			if (HealthComponent->Health == 0)
			{
				Character->InventoryComponent->AddXP(EnemyXP);
				Character->InventoryComponent->AddCoins(EnemyCoins);
				UE_LOG(LogTemp, Warning, TEXT("Character XP: %d"), Character->InventoryComponent->XP);
			}	
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Valid"));
		}
		
			
		
		
			
		
		
		
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

