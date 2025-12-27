// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, MaxHealth);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CACTUSGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = MaxHealth;
	
	void ApplyDamage(float Damage);
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Resistance")
	float DamageResistance = 0.0f;
	UFUNCTION()
	float DamageReduction(float Damage);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
UFUNCTION(BlueprintCallable, Category = "Health")
	void IncreaseMaxHealth();
	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnHealthChanged OnHealthChanged;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
