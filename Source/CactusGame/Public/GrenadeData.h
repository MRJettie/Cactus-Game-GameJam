// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GrenadeData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CACTUSGAME_API UGrenadeData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GrenadeName")
	FName GrenadeName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Radius")
	float GrenadeRadius;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Properties")
	bool ImpactGrenade;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Properties")
	FTimerHandle FuseTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Properties")
	float GrenadeDMG;
	
	
};
