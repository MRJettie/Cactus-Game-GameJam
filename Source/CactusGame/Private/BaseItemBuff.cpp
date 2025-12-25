// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemBuff.h"

#include "ItemBuffs.h"
#include "CactusGame/CactusGameCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseItemBuff::ABaseItemBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Mesh->SetupAttachment(Collider);
	
}

// Called when the game starts or when spawned
void ABaseItemBuff::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

void ABaseItemBuff::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (ItemBuff && ItemBuff->Mesh)
	{
		Mesh->SetStaticMesh(ItemBuff->Mesh);
	}
}

/*void ABaseItemBuff::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACactusGameCharacter* Player = Cast<ACactusGameCharacter>(OtherActor);
	if (Player)
	{
		Player->InventoryComponent->ApplyBuff(ItemBuff);
	}
}
*/

// Called every frame
void ABaseItemBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

