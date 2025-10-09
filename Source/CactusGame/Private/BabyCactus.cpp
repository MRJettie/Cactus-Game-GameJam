// Fill out your copyright notice in the Description page of Project Settings.


#include "BabyCactus.h"

#include "CactusGame/CactusGameCharacter.h"
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
	
}

// Called every frame
void ABabyCactus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABabyCactus::ProgressLevel()
{
	if (GEngine)
	{
		if (bNeedsMet)
        	{
        		Level++;
        		bNeedsMet = false;
				int RandRange = FMath::RandRange(1, 15);
        		NeededAmount+=RandRange;
        		
        	}
	}
	
}

void ABabyCactus::Needsheck()
{
		UE_LOG(LogTemp, Warning, TEXT("Level %d"), Level);
		UE_LOG(LogTemp, Warning, TEXT("Needed Amount %d"), NeededAmount);
	
}

void ABabyCactus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(OtherActor);
	
	Super::NotifyActorBeginOverlap(OtherActor);
	if (Character && Character->InventoryComponent != nullptr)
	{
		if (Character->InventoryComponent->TryRemoveWater(NeededAmount))
		{
			bNeedsMet = true;
			ProgressLevel();
		}
		Needsheck();
	}
	
	
}

// Called to bind functionality to input
void ABabyCactus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

