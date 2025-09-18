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
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cactus Needs")
	int BaseAmount = 1;
};
UCLASS()
class CACTUSGAME_API UCactusConfig : public UPrimaryDataAsset
{
	
	GENERATED_BODY()

public:
	//Creates an array based on the Struct
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cactus Needs")
	TArray<FCactusNeeds> Needs;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cactus Needs")
	int ItemsPerLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cactus Needs")
	float MaxHealth = 100.0f;
	
};
