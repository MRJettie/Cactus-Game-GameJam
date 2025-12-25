// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItemBuff.generated.h"

class UItemBuffs;
class UStaticMeshComponent;
class UBoxComponent;
UCLASS()
class CACTUSGAME_API ABaseItemBuff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItemBuff();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	UItemBuffs* ItemBuff = nullptr; 
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
