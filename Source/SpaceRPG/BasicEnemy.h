// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BasePlayerShip.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasicEnemy.generated.h"

UCLASS()
class SPACERPG_API ABasicEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FTimerHandle WeaponTimer;
	FTimerHandle MovementTimer;
	bool isTimerActive;
	bool isMovementDirectionSet;
	int TimeLeftForMovement;

	UPROPERTY(VIsibleDefaultsOnly)
		FVector EnemyGunOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* EnemyMeshComponent;

	UPROPERTY(EditAnywhere, Category = Movement)
		float EnemySpeed;

	UPROPERTY(EditAnywhere, Category = Movement)
		float MaxEnemyAcceptableRadius;

	UPROPERTY(EditAnywhere, Category = Movement)
		float MinEnemyAcceptableRadius;

	UPROPERTY(EditAnywhere, Category = Movement)
		int EnemyMovementDirection;

	//These variables are responsible for defining the duration of the movement in one direction (used for FMath::RandRange)
	UPROPERTY(EditAnywhere, Category = Movement)
		int MinEnemyMovementDirectionDuration;

	UPROPERTY(EditAnywhere, Category = Movement)
		int MaxEnemyMovementDirectionDuration;

	UPROPERTY(EditAnywhere, Category = Weapon)
		float ShootingSpeed;

	UPROPERTY(EditAnywhere, Category = Weapon)
		int WeaponType;

	UPROPERTY(EditAnywhere, Category = Body)
		int EnemyHealthPoints;

	UPROPERTY(EditAnywhere, Category = Body)
		int ExperienceToGet;

	UPROPERTY(EditAnywhere, Category = Body)
		int CurrencyToGet;

	//In MapChanger movement variables
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector RightUp{};
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector RightDown{};
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector LeftDown{};
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector LeftUp{};

	UFUNCTION()
		void Fire();

	UFUNCTION()
		void FirePhysical(const FVector& EnemyLocation, const FRotator& EnemyRotation, UWorld* World);

	UFUNCTION()
		void FireLaser(const FVector& EnemyLocation, const FRotator& EnemyRotation, UWorld* World);

	UFUNCTION()
		void FirePlasma(const FVector& EnemyLocation, const FRotator& EnemyRotation, UWorld* World);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void StartShooting();

	UFUNCTION()
		void StopShooting();

	UFUNCTION()
		void StartMovement();

	UFUNCTION()
		void UpdateMovementTime();

};
