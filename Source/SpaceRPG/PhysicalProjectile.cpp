// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalProjectile.h"

// Sets default values
APhysicalProjectile::APhysicalProjectile(const FObjectInitializer& ObjectInitializer)
{
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>ProjectileMesh(TEXT("'/Game/Various_Meshes/ProjectileMesh.ProjectileMesh'"));
		if (ProjectileMesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(ProjectileMesh.Object);
		}
		ProjectileMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
		ProjectileMeshComponent->SetNotifyRigidBodyCollision(true);
		ProjectileMeshComponent->SetRelativeScale3D({ 0.5f, 0.5f, 0.5f });
		RootComponent = ProjectileMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>ProjectileMaterial(TEXT("'/Game/Various_Materials/Projectile_Mat.Projectile_Mat'"));
	if (ProjectileMaterial.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(ProjectileMaterial.Object, ProjectileMeshComponent);
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	}
	if(!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(ProjectileMeshComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	ProjectileDMG = 2;
}

