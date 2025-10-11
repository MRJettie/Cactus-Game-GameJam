// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthComponent::HealthIncrease()
{
	if (Health>0)
	{
		MaxHealth += 50;
		Health = MaxHealth;
	}
}

void UHealthComponent::ApplyDamage(float Damage)
{
	if (Health > 0)
	{
		Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
		UE_LOG(LogTemp, Warning, TEXT("Health: %f, Reduced Damage: %f"), Health, Damage);
		if (Health == 0)
		{
			GetOwner()->Destroy();
		}
	}
}


float UHealthComponent::DamageReduction(float Damage)
{
	const float FinalDamage = Damage *(1.0f - DamageResistance);
	return Damage = FinalDamage;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

