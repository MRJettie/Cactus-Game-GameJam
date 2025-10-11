// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseWeapon;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Coins = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int XP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int DmgMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int WaterAmount = 1000;
	UFUNCTION()
	bool TryRemoveWater(int Amount);
	UFUNCTION()
	void CheckWater();

	UFUNCTION()
	void AddXP(int Amount);
	UFUNCTION()
	void AddCoins(int Amount);
	UFUNCTION()
	float AddDmgMultiplier(float Amount);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
