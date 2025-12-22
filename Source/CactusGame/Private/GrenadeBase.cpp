// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeBase.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AGrenadeBase::AGrenadeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void AGrenadeBase::GrenadeExplode()
{
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this)
	;
	if (GrenadeData)
	{
		bool bHit = UKismetSystemLibrary::SphereTraceSingle(this, GetActorLocation(), GetActorLocation(), GrenadeData->GrenadeRadius, UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		Destroy();
	}
	
}

// Called when the game starts or when spawned
void AGrenadeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenadeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

