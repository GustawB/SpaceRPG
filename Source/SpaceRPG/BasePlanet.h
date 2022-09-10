// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstance.h"
#include "Components/StaticMeshComponent.h"
#include "BasePlanet.generated.h"

UCLASS()
class SPACERPG_API ABasePlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* PlanetMeshComponent;

	//Variable responsible for determining whether the player "activated" planet or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActivated;

};
