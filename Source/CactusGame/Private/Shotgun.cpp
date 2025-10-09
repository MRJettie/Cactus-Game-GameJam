// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CactusGame/CactusGameCharacter.h"

AShotgun::AShotgun()
{
	Range = 1000.f;
	MaxMagazine = 8;
	CurrentMagazine = MaxMagazine;
	bAutomatic = false;
	WeaponName = "Shotgun";
	
}

void AShotgun::Fire()
{
	AActor* WeaponOwner = GetOwner();
	if (ACactusGameCharacter* Character = Cast<ACactusGameCharacter>(WeaponOwner))
	{
		UCameraComponent* Camera = Character->GetFirstPersonCameraComponent();
		const int32 Pellets = 10;
		const float HalfAngleRad = FMath::DegreesToRadians(4.f); // tweak for spread
		const FVector Start = Camera->GetComponentLocation();
		const FVector Forward = Camera->GetForwardVector();

		FCollisionQueryParams Params(SCENE_QUERY_STAT(ShotgunTrace), false);
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(Character);

		
		TMap<AActor*, float> DamageBuckets;

		for (int32 i = 0; i < Pellets; ++i)
		{
			const FVector Dir = FMath::VRandCone(Forward, HalfAngleRad); 
			const FVector End = Start + Dir * Range;

			FHitResult Hit;
			if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params)) 
			{
				if (AActor* HitActor = Hit.GetActor())
				{
					DamageBuckets.FindOrAdd(HitActor) += PelletDamage;
				}
			}
			DrawDebugLine(GetWorld(), Start, End, FColor::White, false, 1.f, 0, 0.5f);
		}

		// Apply damage once per actor for all pellets that hit it
		for (const TPair<AActor*, float>& Pair : DamageBuckets)
		{
			UGameplayStatics::ApplyDamage(Pair.Key, Pair.Value, Character->GetController(), this, UDamageType::StaticClass()); 
		}

		ConsumeAmmo(1);
		ShotCooldown();
		if (CurrentMagazine == 0)
		{
			Reload();
		}
	}
}
