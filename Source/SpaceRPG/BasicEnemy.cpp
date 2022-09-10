// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!EnemyMeshComponent)
	{
		EnemyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>NewMesh(TEXT("'/Game/SpaceShips/Bob/Bob.Bob'"));
		if (NewMesh.Succeeded())
		{
			EnemyMeshComponent->SetStaticMesh(NewMesh.Object);
		}
		EnemyMeshComponent->SetRelativeScale3D({ 0.5f, 0.5f, 0.5f });
		EnemyMeshComponent->SetCollisionProfileName("Enemy");
		EnemyMeshComponent->SetNotifyRigidBodyCollision(true);
		EnemyMeshComponent->OnComponentHit.AddDynamic(this, &ABasicEnemy::OnHit);
		RootComponent = EnemyMeshComponent;
	}

	EnemySpeed = 1000.0f;
	MinEnemyAcceptableRadius = 1000.0f;
	MaxEnemyAcceptableRadius = 2000.0f;
	MinEnemyMovementDirectionDuration = 3.0f;
	MaxEnemyMovementDirectionDuration = 5.0f;
	EnemyMovementDirection = 1;
	RightUp = { 0.0f, 0.0f, 1040.0f };
	RightDown = { 0.0f, 0.0f, 1040.0f };
	LeftDown = { 0.0f, 0.0f, 1040.0f };
	LeftUp = { 0.0f, 0.0f, 1040.0f };

	ShootingSpeed = 0.15f;
	EnemyGunOffset = { 200.0f, 0.0f, 0.0f };
	WeaponType = 3;
	isTimerActive = false;
	isMovementDirectionSet = false;
	TimeLeftForMovement = 0.0f;

	EnemyHealthPoints = 100;
	ExperienceToGet = 10;
	CurrencyToGet = 20;
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	ABasePlayerShip* Player = Cast<ABasePlayerShip>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (Player && UGameplayStatics::GetCurrentLevelName(GetWorld()) == "testCombatLevel")
	{
		//Responsible for rotating actor towards player
		FRotator NewRotation{ UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation()) };
		SetActorRotation(NewRotation);

		//Responsible for moving actor towards the player
		float DistanceBetweenActors{ FVector::Distance(GetActorLocation(), Player->GetActorLocation()) };
		if (DistanceBetweenActors <= 3000.0f && isTimerActive == false)
		{
			StartShooting();
			isTimerActive = true;
		}
		else if(DistanceBetweenActors > 3000.0f)
		{
			StopShooting();
			isTimerActive = false;
		}

		if (!isMovementDirectionSet)
		{
			TimeLeftForMovement = FMath::RandRange(MinEnemyMovementDirectionDuration, MaxEnemyMovementDirectionDuration);
			EnemyMovementDirection *= -1;
			StartMovement();
			isMovementDirectionSet = true;
		}

		if (DistanceBetweenActors >= MaxEnemyAcceptableRadius)
			CurrentLocation += (GetActorForwardVector() * EnemySpeed * DeltaTime);
		else if(DistanceBetweenActors < MaxEnemyAcceptableRadius && DistanceBetweenActors>= MinEnemyAcceptableRadius && (EnemyMovementDirection == 1 || EnemyMovementDirection == -1))
			CurrentLocation += (GetActorRightVector() * EnemySpeed * DeltaTime * EnemyMovementDirection);
		else if(DistanceBetweenActors < MinEnemyAcceptableRadius)
			CurrentLocation -= (GetActorForwardVector() * EnemySpeed  * DeltaTime);
		CurrentLocation.Z = 160.0f;
		SetActorLocation(CurrentLocation);

		//handles a situation when an enemy is dead
		if (EnemyHealthPoints <= 0)
		{
			Player->InventorySystem->PlayerExperience += ExperienceToGet;
			Player->InventorySystem->PlayerCurrency += CurrencyToGet;
			Destroy();
		}
	}
	/*else
	{
		if (CurrentLocation != RightUp && CurrentLocation != RightDown && CurrentLocation != LeftDown && CurrentLocation != LeftUp)
		{
			CurrentLocation += (GetActorForwardVector() * EnemySpeed * DeltaTime * EnemyMovementDirection);
			CurrentLocation.Z = 1040.0f;
			SetActorLocation(CurrentLocation);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("EnemyHit"));
			FRotator EnemyRotation{ GetActorRotation() };
			EnemyRotation.Yaw += 90.0f;
			SetActorRotation(EnemyRotation);
			CurrentLocation += (GetActorForwardVector() * EnemySpeed * DeltaTime * EnemyMovementDirection);
			CurrentLocation.Z = 1040.0f;
			SetActorLocation(CurrentLocation);
		}
	}*/

}

void ABasicEnemy::Fire()
{
	FRotator EnemyRotation{ GetActorRotation() };
	FVector EnemyLocation{ GetActorLocation() + EnemyRotation.RotateVector(EnemyGunOffset) };
	UWorld* World = GetWorld();
	if (World)
	{
		switch (WeaponType)
		{
		case 0:	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, TEXT("Enemy weapon int = 0")); break;
		case 1: FirePhysical(EnemyLocation, EnemyRotation, World); break;
		case 2: FireLaser(EnemyLocation, EnemyRotation, World); break;
		case 3: FirePlasma(EnemyLocation, EnemyRotation, World); break;
		default: break;
		}
	}
}

void ABasicEnemy::FirePhysical(const FVector& EnemyLocation, const FRotator& EnemyRotation, UWorld* World)
{
	APhysicalProjectile* Projectile = World->SpawnActor<APhysicalProjectile>(EnemyLocation, EnemyRotation);
	if (Projectile)
	{
		FVector LaunchDirection{ EnemyRotation.Vector() };
		Projectile->FireInDirection(LaunchDirection, EnemySpeed);
	}
}

void ABasicEnemy::FireLaser(const FVector& EnemyLocation, const FRotator& EnemyRotation, UWorld* World)
{
	ALaserProjectile* Projectile = World->SpawnActor<ALaserProjectile>(EnemyLocation, EnemyRotation);
	if (Projectile)
	{
		FVector LaunchDirection{ EnemyRotation.Vector() };
		Projectile->FireInDirection(LaunchDirection, EnemySpeed);
	}
}

void ABasicEnemy::FirePlasma(const FVector& EnemyLocation, const FRotator& EnemyRotation, UWorld* World)
{
	APlasmaProjectile* Projectile = World->SpawnActor<APlasmaProjectile>(EnemyLocation, EnemyRotation);
	if (Projectile)
	{
		FVector LaunchDirection{ EnemyRotation.Vector() };
		Projectile->FireInDirection(LaunchDirection, EnemySpeed);
	}
}

void ABasicEnemy::StartShooting()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "StartShooting");
	GetWorldTimerManager().SetTimer(WeaponTimer, this, &ABasicEnemy::Fire, ShootingSpeed, true, 0.0f);
}

void ABasicEnemy::StopShooting()
{
	GetWorldTimerManager().ClearTimer(WeaponTimer);
}

void ABasicEnemy::StartMovement()
{
	GetWorldTimerManager().SetTimer(MovementTimer, this, &ABasicEnemy::UpdateMovementTime, 1.0f, true, 0.0f);
}

void ABasicEnemy::UpdateMovementTime()
{
	--TimeLeftForMovement;
	if ((TimeLeftForMovement == 0))
	{
		GetWorldTimerManager().ClearTimer(MovementTimer);
		isMovementDirectionSet = false;
	}
}

void ABasicEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("EnemyHit"));
	if (OtherActor != this)
	{
		ABasicProjectile* Projectile = Cast<ABasicProjectile>(OtherActor);
		if (Projectile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%lld"), Projectile->ProjectileDMG));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("%lld"), EnemyHealthPoints));
			EnemyHealthPoints -= Projectile->ProjectileDMG;
			Projectile->Destroy();
		}
	}
}

