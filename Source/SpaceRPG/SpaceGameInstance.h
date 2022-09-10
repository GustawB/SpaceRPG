// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACERPG_API USpaceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	USpaceGameInstance(const FObjectInitializer& ObjectInitializer);

	//Weapon type variables
	UPROPERTY()
		int MainWeapon;

	UPROPERTY()
		int SpecialWeapon;

	//Ship type variable
	UPROPERTY()
		int ShipType;

	//Player variables
	UPROPERTY()
		int PlayerHealthPoints;

	bool bShouldUpdateEquipment;

	FString MapName;
	
};
