// Fill out your copyright notice in the Description page of Project Settings.


#include "NuclearRocketSpecial.h"

// Sets default values
ANuclearRocketSpecial::ANuclearRocketSpecial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!NuclearMeshComponent)
	{
		NuclearMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NuclearMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>NuclearMesh(TEXT("StaticMesh'/Game/Various_Meshes/NuclearMesh.NuclearMesh'"));
		if (NuclearMesh.Succeeded())
		{
			NuclearMeshComponent->SetStaticMesh(NuclearMesh.Object);
		}
		NuclearMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
		NuclearMeshComponent->SetRelativeScale3D({ 3.0f, 3.0f, 3.0f });
		NuclearMeshComponent->SetRelativeRotation({ 90.0f, 0.0f, 0.0f });
		RootComponent = NuclearMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>NuclearMaterial(TEXT("'/Game/Various_Materials/Projectile_Mat.Projectile_Mat'"));
	if (NuclearMaterial.Succeeded())
	{
		NuclearMaterialInstance = UMaterialInstanceDynamic::Create(NuclearMaterial.Object, NuclearMeshComponent);
		NuclearMeshComponent->SetMaterial(0, NuclearMaterialInstance);
	}
	//if (!ProjectileCollisionComponent)
	//{
	//	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
	//	ProjectileCollisionComponent->SetupAttachment(RootComponent);
	//}
	if (!NuclearMovementComponent)
	{
		NuclearMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("NuclearMovementComponent"));
		NuclearMovementComponent->SetUpdatedComponent(NuclearMeshComponent);
		NuclearMovementComponent->InitialSpeed = 1500.0f;
		NuclearMovementComponent->MaxSpeed = 1500.0f;
		NuclearMovementComponent->bShouldBounce = false;
		NuclearMovementComponent->ProjectileGravityScale = 0.0f;
	}
	//deleting projectile after X seconds
	InitialLifeSpan = 20.0f;
}

// Called when the game starts or when spawned
void ANuclearRocketSpecial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANuclearRocketSpecial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANuclearRocketSpecial::FireInDirection(const FVector& ShootingDirection, float MoveSpeeed)
{
	NuclearMovementComponent->Velocity = ShootingDirection * (NuclearMovementComponent->InitialSpeed + MoveSpeeed);
}

