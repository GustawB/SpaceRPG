// Fill out your copyright notice in the Description page of Project Settings.


#include "BigLaserSpecial.h"

// Sets default values
ABigLaserSpecial::ABigLaserSpecial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BigLaserSpecialRootComponent"));
	}
	if (!SpecLaserMeshComponent)
	{
		SpecLaserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BigLaserSpecialMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SpecLaserMesh(TEXT("'/Game/Various_Meshes/BigLaserMesh2.BigLaserMesh2'"));
		if (SpecLaserMesh.Succeeded())
		{
			SpecLaserMeshComponent->SetStaticMesh(SpecLaserMesh.Object);
		}
		SpecLaserMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
		SpecLaserMeshComponent->SetRelativeScale3D({ 0.5f, 0.5f, 0.5f });
		RootComponent = SpecLaserMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>SpecLasereMaterial(TEXT("'/Game/Various_Materials/Projectile_Mat.Projectile_Mat'"));
	if (SpecLasereMaterial.Succeeded())
	{
		SpecLaserMaterialInstance = UMaterialInstanceDynamic::Create(SpecLasereMaterial.Object, SpecLaserMeshComponent);
		SpecLaserMeshComponent->SetMaterial(0, SpecLaserMaterialInstance);
	}
	InitialLifeSpan = 10.0f;
	//SpecLaserMeshComponent->SetRelativeScale3D({ 2.0f, 1.0f, 1.0f });
	/*if (!SpecLaserMovementComponent)
	{
		SpecLaserMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SpecLaserMovementComponent"));
		SpecLaserMovementComponent->SetUpdatedComponent(SpecLaserMeshComponent);
		SpecLaserMovementComponent->InitialSpeed = 3000.0f;
		SpecLaserMovementComponent->MaxSpeed = 3000.0f;
		SpecLaserMovementComponent->bShouldBounce = false;
		SpecLaserMovementComponent->ProjectileGravityScale = 0.0f;
	}
	//deleting projectile after X seconds
	InitialLifeSpan = 3.0f;*/
}

// Called when the game starts or when spawned
void ABigLaserSpecial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABigLaserSpecial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

