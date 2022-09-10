// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "BasePlayerShip.h"
#include "Materials/MaterialInstance.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
//#include "BasicEnemy.h"
#include "BasicProjectile.generated.h"

UCLASS()
class SPACERPG_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstance* ProjectileMaterialInstance;

	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY()
		int ProjectileDMG;

	UFUNCTION()
		void FireInDirection(const FVector& ShootingDirection, float MoveSpeeed);

};
