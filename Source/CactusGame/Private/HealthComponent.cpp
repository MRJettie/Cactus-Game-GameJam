// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
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


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();


	
}



void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

