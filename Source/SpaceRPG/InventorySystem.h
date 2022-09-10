// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySystem.generated.h"



/*USTRUCT(BlueprintType)
struct SPACERPG_API FWeaponsTypesEquipped
{
	GENERATED_BODY()

	UPROPERTY()
		int MainWeapon;

	UPROPERTY()
		int SpecialWeapon;
};

USTRUCT(BlueprintType)
struct SPACERPG_API FAmmoAvailable
{
	GENERATED_BODY()

		UPROPERTY()
		int ProjectileAmmo;

	UPROPERTY()
		int LaserAmmo;

	UPROPERTY()
		int PlasmaAmmo;
};*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACERPG_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Weapon type variables
	UPROPERTY(BlueprintReadWrite)
		int MainWeapon;

	UPROPERTY(BlueprintReadWrite)
		int SpecialWeapon;

	//Ship type variable
	UPROPERTY(BlueprintReadWrite)
		int ShipType;

	//Responsible for updating variables in GameInstance e.g. when changing level
	UFUNCTION()
		void SaveDataToGameInstance();

	//Body Variables

	UPROPERTY(BlueprintReadWrite)
		int PlayerHealthPoints;

	UPROPERTY(BlueprintReadWrite)
		int PlayerExperience;

	UPROPERTY(BlueprintReadWrite)
		int PlayerLevel;

	UPROPERTY(BlueprintReadWrite)
		int PlayerCurrency;

};
