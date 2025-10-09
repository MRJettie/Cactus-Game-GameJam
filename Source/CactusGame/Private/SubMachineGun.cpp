// Fill out your copyright notice in the Description page of Project Settings.


#include "SubMachineGun.h"

ASubMachineGun::ASubMachineGun()
{
	MaxMagazine = 25;
	CurrentMagazine = MaxMagazine;
	Range = 1000.f;
	Damage = 10;
	WeaponName = "Sub MachineGun";
	FireRate = 20.f;
	bAutomatic = true;
}
