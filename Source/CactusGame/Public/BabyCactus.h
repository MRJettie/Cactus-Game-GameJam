// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BabyCactus.generated.h"
class UStaticMeshComponent;
class UBoxComponent;

//Struct for the stages of the cactus
USTRUCT(BlueprintType)
struct FCactusLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cactus Needs")
	TMap <FName, int> Requirements;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cactus Needs")
	float LevelTimer;
	
};

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

	//Cactus Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cactus Needs")
	int NeededAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cactus Needs")
	int Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cactus Needs")
	bool bNeedsMet;
	UFUNCTION()
	void ProgressLevel();
	void Needsheck();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
