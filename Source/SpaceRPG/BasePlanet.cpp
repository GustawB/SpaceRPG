// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlanet.h"

// Sets default values
ABasePlanet::ABasePlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!PlanetMeshComponent)
	{
		PlanetMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMeshComponent"));
		RootComponent = PlanetMeshComponent;
		PlanetMeshComponent->SetCollisionProfileName(TEXT("Planet"));
	}
	
	bIsActivated = false;
}

// Called when the game starts or when spawned
void ABasePlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

