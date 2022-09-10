// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MainWeapon = 2;
	SpecialWeapon = 1;
	ShipType = 0;

	//else
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Nullptr Instance"));

}


// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	USpaceGameInstance* SpaceGameInstace = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (SpaceGameInstace)
	{
		MainWeapon = SpaceGameInstace->MainWeapon;
		SpecialWeapon = SpaceGameInstace->SpecialWeapon;
		ShipType = SpaceGameInstace->ShipType;
		PlayerHealthPoints = SpaceGameInstace->PlayerHealthPoints;
	}
	
}


// Called every frame
void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventorySystem::SaveDataToGameInstance()
{
	USpaceGameInstance* SpaceGameInstace = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (SpaceGameInstace == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Nullptr Instance"));
	SpaceGameInstace->MainWeapon = MainWeapon;
	SpaceGameInstace->SpecialWeapon = SpecialWeapon;
	SpaceGameInstace->ShipType = ShipType;
	SpaceGameInstace->PlayerHealthPoints = PlayerHealthPoints;
}
