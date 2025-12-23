// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemBuff.h"

#include "ItemBuffs.h"

// Sets default values
ABaseItemBuff::ABaseItemBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ABaseItemBuff::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

// Called every frame
void ABaseItemBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

