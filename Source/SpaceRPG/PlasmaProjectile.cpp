// Fill out your copyright notice in the Description page of Project Settings.


#include "PlasmaProjectile.h"

// Sets default values
APlasmaProjectile::APlasmaProjectile(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>PlasmaMesh(TEXT("'/Game/Various_Meshes/PlasmaMesh.PlasmaMesh'"));
		if (PlasmaMesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(PlasmaMesh.Object);
		}
		ProjectileMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
		ProjectileMeshComponent->SetRelativeScale3D({ 0.6f, 0.6f, 0.6f });
		RootComponent = ProjectileMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>LaserMaterial(TEXT("'/Game/Various_Materials/Plasma_Mat.Plasma_Mat'"));
	if (LaserMaterial.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(LaserMaterial.Object, ProjectileMeshComponent);
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	}
	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(ProjectileMeshComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	ProjectileDMG = 3;

}



