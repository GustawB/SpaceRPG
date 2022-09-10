// Fill out your copyright notice in the Description page of Project Settings.


#include "MapChanger.h"

// Sets default values
AMapChanger::AMapChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!MapChangerMeshComponent)
	{
		MapChangerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapChangerMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>NewMesh(TEXT("'/Game/Various_Meshes/MapActivatorThird_Mesh.MapActivatorThird_Mesh'"));
		if (NewMesh.Succeeded())
		{
			MapChangerMeshComponent->SetStaticMesh(NewMesh.Object);
		}
		MapChangerMeshComponent->SetCollisionProfileName("MapChanger");
		MapChangerMeshComponent->SetNotifyRigidBodyCollision(true);
		MapChangerMeshComponent->OnComponentHit.AddDynamic(this, &AMapChanger::OnHit);
		RootComponent = MapChangerMeshComponent;
	}

}

// Called when the game starts or when spawned
void AMapChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapChanger::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("MapChangerHit"));
}

