// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CactusConfig.h"
#include "BabyCactus.generated.h"
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CACTUSGAME_API ABabyCactus : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABabyCactus();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DemandCurve;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CactusConfig)
	UCactusConfig* Config = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
