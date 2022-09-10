// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstance.h"
#include "BigLaserSpecial.generated.h"

UCLASS()
class SPACERPG_API ABigLaserSpecial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigLaserSpecial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* SpecLaserMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstance* SpecLaserMaterialInstance;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* SpecLaserMovementComponent;

};
