// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ItemBuffs.h"
#include "Engine/Engine.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

bool UInventoryComponent::TryRemoveWater(int Amount)
{
	if (WaterAmount >= Amount)
	{
		WaterAmount -= Amount;
		return true;
	}
	return false;
}

void UInventoryComponent::CheckWater()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Water: %d"), WaterAmount));
	}
}

void UInventoryComponent::AddXP(int Amount)
{
	XP+=Amount;
	while (XP >= XPToLevel)
	{
		
		int RemainderXP = XP - XPToLevel;
		int XPIncrease = XPToLevel + Level * 124;
		Level++;
		XPToLevel = XPIncrease;
		XP = RemainderXP;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Level: %d"), Level));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("XP: %d"), XP));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("XPToLevel: %d"), XPToLevel));
		}
		
	}
	OnXPChanged.Broadcast(XP,XPToLevel);
}

void UInventoryComponent::AddCoins(int Amount)
{
	Coins += Amount;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Coins: %d"), Coins));
	}
}

float UInventoryComponent::AddDmgMultiplier(float Amount)
{
	DmgMultiplier *= Amount;
	return Amount;
}

void UInventoryComponent::ApplyBuff(const UItemBuffs* Buffs)
{
	if (Buffs)
	{
		if (Buffs->DMGModifier != 1)
		{
			DmgMultiplier *= Buffs->DMGModifier;
		}
		if (Buffs->SpeedModifier != 1)
		{
			SpeedMultiplier *= Buffs->SpeedModifier;
		}
	}
	
}


void UInventoryComponent::BeginPlay()
{
	OnXPChanged.Broadcast(XP,XPToLevel);
	Super::BeginPlay();


	
}



void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

