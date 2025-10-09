// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

AAssaultRifle::AAssaultRifle()
{
	MaxMagazine = 30;
	CurrentMagazine = MaxMagazine;
	Range = 1000.f;
	Damage = 20;
	WeaponName = "Assault Rifle";
}
