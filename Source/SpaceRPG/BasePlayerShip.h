// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
//Projectiles
#include "PhysicalProjectile.h"
#include "LaserProjectile.h"
#include "PlasmaProjectile.h"
#include "BigLaserSpecial.h"
#include "NuclearRocketSpecial.h"
#include "SmallRocketsSpecial.h"
//inventory
#include "InventorySystem.h"
//Planet
#include "BasePlanet.h"
//
#include "MapChanger.h"
#include "SpaceGameInstance.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerShip.generated.h"

UCLASS()
class SPACERPG_API ABasePlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePlayerShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector MovementDirection;

	UPROPERTY(EditAnywhere, Category = Movement)
		float MovementSpeed{ 500.0f };

	UPROPERTY(EditAnywhere, Category = Shooting)
		float ShootingSpeed{ 0.1f };

	UPROPERTY(EditAnywhere, Category = Shooting)
		float SpecialShootingSpeed{ 10.0f };

	UPROPERTY(VIsibleDefaultsOnly)
		FVector GunOffset;

	UPROPERTY(VisibleDefaultsOnly)
		FVector SpecialGunOffset;


	//timer object for managing auto-fire
	FTimerHandle WeaponTimer;
	FTimerHandle SpecialWeaponTimer;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* ShipActivationRange;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* EnemyMovementBorder;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* TopDownCamera;

	UPROPERTY(BlueprintReadwrite)
		UInventorySystem* InventorySystem;

	/// //////////////////////////Ships///////////////////////////////////////
	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* BobMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* ChallengerMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* DispatcherMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* ExecutionerMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* ImperialMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* InsurgentMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* OmenMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* PancakeMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* SpitfireMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* StrikerMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* ZenithMesh;
	/// ////////////////////////Ships/////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float MoveSpeed;

	UPROPERTY(BlueprintReadWrite)
		int SpecLaserCoolDown;

	UFUNCTION()
		void StartShooting();

	UFUNCTION()
		void StopShooting();

	UFUNCTION()
		void Fire();

	UFUNCTION()
		void FireSpecial();

	UFUNCTION()
		void StartShootingSpecialWeapon();

	UFUNCTION()
		void StopShootingSpecialWeapon();

	UFUNCTION()
		void FirePhysical(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World);

	UFUNCTION()
		void FireLaser(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World);

	UFUNCTION()
		void FirePlasma(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World);

	UFUNCTION()
		void FireSpecLaser(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World);

	UFUNCTION()
		void FireNuclearSpecial(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World);

	UFUNCTION()
		void FireSmallSpecial(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World);

	UFUNCTION()
		void Interaction();

	UFUNCTION()
		void ChangeLevel();

	UFUNCTION()
		void RotateActor(float RotationValue);

	UFUNCTION(BlueprintCallable)
		void ChangeShip(int ShipType);

	UFUNCTION()
		void ChangeShipParams(UStaticMesh* StaticMesh, const float SphereRadius, const float NewGunOffset, const float NewArmLength);

	UFUNCTION()
		void CooldownPassing();

	UPROPERTY()
		bool bIsDefaultMapOn;

	UPROPERTY()
		float RotatationSpeed;

	UPROPERTY(BlueprintReadWrite)
		float defaultTargetOffsetZ;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FRotator CurrentRotation;
	double FiringModification;

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName RotateRightBinding;
	//float determining shooting speed

};
