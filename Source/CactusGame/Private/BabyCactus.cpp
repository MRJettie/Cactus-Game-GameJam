// Fill out your copyright notice in the Description page of Project Settings.


#include "BabyCactus.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
// Sets default values
ABabyCactus::ABabyCactus()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh->SetupAttachment(Box);

}

// Called when the game starts or when spawned
void ABabyCactus::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		if (Config)
		{
			for (const FCactusNeeds& Entry : Config->Needs)
			{
			 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Tag: %s, Amount: %d"), *Entry.ItemTag.ToString(), Entry.BaseAmount));
			}
		}
	}
}

// Called every frame
void ABabyCactus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABabyCactus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

