// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstance.h"
#include "NuclearRocketSpecial.generated.h"

UCLASS()
class SPACERPG_API ANuclearRocketSpecial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANuclearRocketSpecial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* NuclearMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstance* NuclearMaterialInstance;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* NuclearMovementComponent;

	UFUNCTION()
		void FireInDirection(const FVector& ShootingDirection, float MoveSpeeed);

};
