// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class CACTUSGAME_API AShotgun : public ABaseWeapon
{
	GENERATED_BODY()
	AShotgun();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shotgun")
	float PelletDamage = 4.f;
	virtual void Fire() override;
	
};
