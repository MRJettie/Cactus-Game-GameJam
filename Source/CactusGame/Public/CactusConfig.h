// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CactusConfig.generated.h"

USTRUCT(BlueprintType)
struct FCactusNeeds
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cactus Needs")
	TMap <FName, int> Requirements;
	
};
UCLASS()
class CACTUSGAME_API UCactusConfig : public UPrimaryDataAsset
{
	
	GENERATED_BODY()

public:
	//Creates an array based on the Struct
	UPROPERTY(EditAnywhere, Category = "Cactus Needs")
	int CurrentLevel;
	UPROPERTY(EditAnywhere, Category = "Cactus Needs")
	float MaxHealth = 100.0f;
	UFUNCTION()
	void ItemCheck();
};
