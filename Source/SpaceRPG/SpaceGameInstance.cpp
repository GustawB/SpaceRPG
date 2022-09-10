// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceGameInstance.h"

USpaceGameInstance::USpaceGameInstance(const FObjectInitializer& ObjectInitializer)
{
	//MainWeapon = 0;
	SpecialWeapon = 3;
	//ShipType = 0;
	PlayerHealthPoints = 100.0f;
	bShouldUpdateEquipment = false;

}
