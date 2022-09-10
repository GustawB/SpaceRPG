// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//deleting projectile after X seconds
	InitialLifeSpan = 3.0f;

	ProjectileDMG = 10;

}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicProjectile::FireInDirection(const FVector& ShootingDirection, float MoveSpeed)
{
	ProjectileMovementComponent->Velocity = ShootingDirection * (ProjectileMovementComponent->InitialSpeed + MoveSpeed);
}



