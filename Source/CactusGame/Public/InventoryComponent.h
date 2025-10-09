// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
	struct FInventoryItem
	{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int Amount;
		
	};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CACTUSGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	int Coins = 0;
	int XP = 0;
	int WaterAmount = 1000;
	UFUNCTION()
	bool TryRemoveWater(int Amount);
	UFUNCTION()
	void CheckWater();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
