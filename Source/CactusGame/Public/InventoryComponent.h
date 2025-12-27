// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnXPChanged, int32, NewXP, int32, NewXPToLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsChanged, int32, NewCoins);

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CACTUSGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Coins = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int CoinMultiplier = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int XPToLevel = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int XP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int DmgMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int SpeedMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int WaterAmount = 1000;
	UFUNCTION()
	bool TryRemoveWater(int Amount);
	UFUNCTION()
	void CheckWater();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddXP(int Amount);
	UFUNCTION()
	void AddCoins(int Amount);
	UFUNCTION()
	float AddDmgMultiplier(float Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ApplyBuff(const UItemBuffs* Buffs);

	//Events
	UPROPERTY(BlueprintAssignable, Category="XP")
	FOnXPChanged OnXPChanged;
	UPROPERTY(BlueprintAssignable, Category="Coins")
	FOnCoinsChanged OnCoinsChanged;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
