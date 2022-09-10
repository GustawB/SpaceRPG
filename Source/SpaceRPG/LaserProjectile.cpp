// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserProjectile.h"

// Sets default values
ALaserProjectile::ALaserProjectile(const FObjectInitializer& ObjectInitializer)
{
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>ProjectileMesh(TEXT("'/Game/Various_Meshes/LaserMesh.LaserMesh'"));
		if (ProjectileMesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(ProjectileMesh.Object);
		}
		ProjectileMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
		ProjectileMeshComponent->SetRelativeScale3D({ 0.5f, 0.5f, 0.5f });
		ProjectileMeshComponent->SetRelativeRotation({ 0.0f, 90.0f, 0.0f });
		RootComponent = ProjectileMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>ProjectileMaterial(TEXT("'/Game/Various_Materials/Laser_Mat.Laser_Mat'"));
	if (ProjectileMaterial.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(ProjectileMaterial.Object, ProjectileMeshComponent);
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	}
	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	}
	
	ProjectileDMG = 1;
}

