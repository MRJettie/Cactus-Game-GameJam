// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataAsset.h"
#include "ItemBuffs.generated.h"

/**
 * 
 */

UCLASS()
class CACTUSGAME_API UItemBuffs : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	int DMGModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	float SpeedModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")	
	float HealthModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	float ArmorModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	float CooldownModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	int JumpModifier;
	
	
};
