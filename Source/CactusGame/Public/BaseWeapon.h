// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"
class UStaticMeshComponent;
class UBoxComponent;
class USkeletalMeshComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int, CurrentAmmo, int, MaxAmmo);

UCLASS()
class CACTUSGAME_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	
	ABaseWeapon();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Properties")
	int MaxMagazine;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Properties")
	int CurrentMagazine = MaxMagazine;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Properties")
	float Range = 200;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Properties")
	float ReloadTime = 2.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Properties")
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FName WeaponName;
	UPROPERTY(EditDefaultsOnly, Category="Firing")
	bool bAutomatic = false;
	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float FireRate = 10.f;
	FTimerHandle FireTimer;
	UPROPERTY(EditDefaultsOnly, Category="Firing")
	bool bIsReloading = false;
	UPROPERTY(EditDefaultsOnly, Category="Firing")
	float NextShot = 0.0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAmmoChanged OnAmmoChanged;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ForceBroadcastAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ConsumeAmmo(int Amount);

	
	//Functions for Weapons
	virtual void Reload();
	virtual void Fire();
	virtual void StartFiring();
	virtual void StopFiring();
	virtual bool CanFire() const;
	virtual void ShotCooldown();
	UFUNCTION()
	float CalculateDamage();
	void DropWeapon(AActor* OwnerActor, float Distance);


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* AmmoMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void DisablePhysics();
	void EnablePhysics(const FVector& Impulse);

};
