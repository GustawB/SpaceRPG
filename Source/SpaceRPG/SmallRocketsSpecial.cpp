// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallRocketsSpecial.h"

// Sets default values
ASmallRocketsSpecial::ASmallRocketsSpecial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!SmallMeshComponent)
	{
		SmallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NuclearMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SmallMesh(TEXT("'/Game/Various_Meshes/NuclearMesh.NuclearMesh'"));
		if (SmallMesh.Succeeded())
		{
			SmallMeshComponent->SetStaticMesh(SmallMesh.Object);
		}
		SmallMeshComponent->BodyInstance.SetCollisionProfileName("Projectile");
		SmallMeshComponent->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });
		SmallMeshComponent->SetRelativeRotation({ 90.0f, 0.0f, 0.0f });
		RootComponent = SmallMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>SmallMaterial(TEXT("'/Game/Various_Materials/SmallRocketMaterial.SmallRocketMaterial'"));
	if (SmallMaterial.Succeeded())
	{
		SmallMaterialInstance = UMaterialInstanceDynamic::Create(SmallMaterial.Object, SmallMeshComponent);
		SmallMeshComponent->SetMaterial(0, SmallMaterialInstance);
	}
	//if (!ProjectileCollisionComponent)
	//{
	//	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
	//	ProjectileCollisionComponent->SetupAttachment(RootComponent);
	//}
	if (!SmallMovementComponent)
	{
		SmallMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("NuclearMovementComponent"));
		SmallMovementComponent->SetUpdatedComponent(SmallMeshComponent);
		SmallMovementComponent->InitialSpeed = 1500.0f;
		SmallMovementComponent->MaxSpeed = 1500.0f;
		SmallMovementComponent->bShouldBounce = false;
		SmallMovementComponent->ProjectileGravityScale = 0.0f;
	}
	//deleting projectile after X seconds
	InitialLifeSpan = 20.0f;

}

// Called when the game starts or when spawned
void ASmallRocketsSpecial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmallRocketsSpecial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASmallRocketsSpecial::FireInDirection(const FVector& ShootingDirection, float MoveSpeeed)
{
	SmallMovementComponent->Velocity = ShootingDirection * (SmallMovementComponent->InitialSpeed + MoveSpeeed);
}

