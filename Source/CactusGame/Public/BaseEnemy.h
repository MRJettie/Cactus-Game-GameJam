// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"
class UStaticMeshComponent;
class UHealthComponent;
class UBoxComponent;
UCLASS()
class CACTUSGAME_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Drop Value")
	int EnemyXP = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Drop Value")
	int EnemyCoins = 5;
	//Functions of the Class
	UFUNCTION()
	virtual void Patrol();
	UFUNCTION()
	virtual void Attack();
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
