// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerShip.h"


const FName ABasePlayerShip::MoveForwardBinding("MoveForward");
const FName ABasePlayerShip::MoveRightBinding("MoveRight");
const FName ABasePlayerShip::RotateRightBinding("MouseMovement");

// Sets default values
ABasePlayerShip::ABasePlayerShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	if (!InventorySystem)
	{
		InventorySystem = CreateDefaultSubobject<UInventorySystem>(TEXT("InventorySystem"));
	}
	if (!ShipMeshComponent)
	{
		ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>NewMesh(TEXT("'/Game/SpaceShips/Bob/Bob.Bob'"));
		if (NewMesh.Succeeded())
		{
			BobMesh = NewMesh.Object;
			ShipMeshComponent->SetStaticMesh(BobMesh);
		}
		//Responsible for simulating hit events
		ShipMeshComponent->SetCollisionProfileName("Player");
		ShipMeshComponent->SetNotifyRigidBodyCollision(true);
		ShipMeshComponent->OnComponentHit.AddDynamic(this, &ABasePlayerShip::OnHit);
		RootComponent = ShipMeshComponent;
	}
	if (!ShipActivationRange)
	{
		ShipActivationRange = CreateDefaultSubobject<USphereComponent>(TEXT("ShipCollisionComponent"));
		ShipActivationRange->SetupAttachment(RootComponent);
		ShipActivationRange->SetSphereRadius(600.0f);
		ShipActivationRange->SetCollisionProfileName(TEXT("ActivationRange"));
	}
	//camera height handled by SpringArm
	defaultTargetOffsetZ = 4000.0f;
	if (!CameraSpringArm)
	{
		CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
		CameraSpringArm->SetupAttachment(RootComponent);
		CameraSpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
		CameraSpringArm->TargetArmLength = 1200.f;
		CameraSpringArm->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
		CameraSpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
		CameraSpringArm->TargetOffset.Z = defaultTargetOffsetZ;
	}
	if (!TopDownCamera)
	{
		TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
		TopDownCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
		TopDownCamera->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	}

//////Different meshes for the ship/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindChallenger(TEXT("'/Game/SpaceShips/Challenger/Challenger.Challenger'"));
	if (FindChallenger.Succeeded())
		ChallengerMesh = FindChallenger.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindDispatcher(TEXT("'/Game/SpaceShips/Dispatcher/Dispatcher.Dispatcher'"));
	if (FindDispatcher.Succeeded())
		DispatcherMesh = FindDispatcher.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindExecutioner(TEXT("'/Game/SpaceShips/Executioner/Executioner.Executioner'"));
	if (FindExecutioner.Succeeded())
		ExecutionerMesh = FindExecutioner.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindImperial(TEXT("'/Game/SpaceShips/Imperial/Imperial.Imperial'"));
	if (FindImperial.Succeeded())
		ImperialMesh = FindImperial.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindInsurgent(TEXT("'/Game/SpaceShips/Insurgent/Insurgent.Insurgent'"));
	if (FindInsurgent.Succeeded())
		InsurgentMesh = FindInsurgent.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindOmen(TEXT("'/Game/SpaceShips/Omen/Omen.Omen'"));
	if (FindOmen.Succeeded())
		OmenMesh = FindOmen.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindPancake(TEXT("'/Game/SpaceShips/Pancake/Pancake.Pancake'"));
	if (FindPancake.Succeeded())
		PancakeMesh = FindPancake.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindSpitfire(TEXT("'/Game/SpaceShips/Spitfire/Spitfire.Spitfire'"));
	if (FindSpitfire.Succeeded())
		SpitfireMesh = FindSpitfire.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindStriker(TEXT("'/Game/SpaceShips/Striker/Striker.Striker'"));
	if (FindStriker.Succeeded())
		StrikerMesh = FindStriker.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindZenith(TEXT("'/Game/SpaceShips/Zenith/Zenith.Zenith'"));
	if (FindZenith.Succeeded())
		ZenithMesh = FindZenith.Object;
	//////Different meshes for the ship/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Movement
	MoveSpeed = 2000.0f;
	ShootingSpeed = 0.15f;

	GunOffset = { 200.0f, 0.0f, 0.0f };
	SpecialGunOffset = { 500.0f, 0.0f, 0.0f };

	bIsDefaultMapOn = true;
	RotatationSpeed = 200.0f;
	FiringModification = 0.0f;

}

// Called when the game starts or when spawned
void ABasePlayerShip::BeginPlay()
{
	Super::BeginPlay();

	CameraSpringArm->TargetOffset.Z = defaultTargetOffsetZ;
	ChangeShip(InventorySystem->ShipType);
	
}

// Called to bind functionality to input
void ABasePlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis("RotateRight", this, &ABasePlayerShip::RotateActor);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayerShip::StartShooting);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABasePlayerShip::StopShooting);
	PlayerInputComponent->BindAction("SpecialWeapon", IE_Pressed, this, &ABasePlayerShip::StartShootingSpecialWeapon);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ABasePlayerShip::Interaction);
	//PlayerInputComponent->BindAction("ChangeMap", IE_Pressed, this, &ABasePlayerShip::ChangeLevel);

}

void ABasePlayerShip::ChangeLevel()
{
	UWorld* World = GetWorld();
	FString CurrentLevel = World->GetMapName();
	InventorySystem->SaveDataToGameInstance();
	//UEDPIE_0_ is part of the map's name, not defined by me
	USpaceGameInstance* SpaceGameInstance = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	SpaceGameInstance->bShouldUpdateEquipment = true;
	if (CurrentLevel == "UEDPIE_0_NewWorld")
	{
		UGameplayStatics::OpenLevel(GetWorld(), "testCombatLevel");
		bIsDefaultMapOn = false;
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "NewWorld");
		bIsDefaultMapOn = true;
	}
}

void ABasePlayerShip::RotateActor(float RotationValue)
{
	CurrentRotation = { CurrentRotation.Euler().Y, RotationValue * RotatationSpeed,  0.0f };
}

void ABasePlayerShip::ChangeShipParams(UStaticMesh* StaticMesh, const float SphereRadius, const float NewGunOffset, const float NewArmLength)
{
	ShipMeshComponent->SetStaticMesh(StaticMesh);
	ShipActivationRange->SetSphereRadius(SphereRadius);
	GunOffset.X = NewGunOffset;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%lld"), CameraSpringArm->TargetOffset.Z));
	CameraSpringArm->TargetOffset.Z = NewArmLength;
}

void ABasePlayerShip::CooldownPassing()
{
	--SpecLaserCoolDown;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%lld"), SpecLaserCoolDown));
	if (SpecLaserCoolDown == 0)
		GetWorldTimerManager().ClearTimer(SpecialWeaponTimer);
}

void ABasePlayerShip::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Hit on Player mesh registered"));
	if (OtherActor != this)
	{
		ABasicProjectile* Projectile = Cast<ABasicProjectile>(OtherActor);
		if (Projectile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%lld"), Projectile->ProjectileDMG));
			InventorySystem->PlayerHealthPoints -= Projectile->ProjectileDMG;
			Projectile->Destroy();
		}
	}
}

void ABasePlayerShip::ChangeShip(int ShipType)
{	
	switch (ShipType)
	{
	case 1: ChangeShipParams(BobMesh, 600.0f, 400.0f, defaultTargetOffsetZ); break;
	case 2: ChangeShipParams(ChallengerMesh, 800.0f, 400.0f, defaultTargetOffsetZ); break;
	case 3: ChangeShipParams(DispatcherMesh, 800.0f, 400.0f, defaultTargetOffsetZ); break;
	case 4: ChangeShipParams(ExecutionerMesh, 800.0f, 400.0f, defaultTargetOffsetZ); break;
	case 5: ChangeShipParams(ImperialMesh, 1500.0f, 700.0f, defaultTargetOffsetZ + 1000.0f); break;
	case 6: ChangeShipParams(InsurgentMesh, 800.0f, 500.0f, defaultTargetOffsetZ); break;
	case 7: ChangeShipParams(OmenMesh, 1000.0f, 500.0f, defaultTargetOffsetZ); break;
	case 8: ChangeShipParams(PancakeMesh, 700.0f, 300.0f, defaultTargetOffsetZ); break;
	case 9: ChangeShipParams(SpitfireMesh, 700.0f, 300.0f, defaultTargetOffsetZ); break;
	case 10: ChangeShipParams(StrikerMesh, 700.0f, 300.0f, defaultTargetOffsetZ); break;
	case 11: ChangeShipParams(ZenithMesh, 800.0f, 500.0f, defaultTargetOffsetZ); break;
	default: GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error in mesh switch")); break;

	}
}

// ///////////////////////////TIMERS/////////////////////////////////////////////////////////////////////////////////////////////////////
void ABasePlayerShip::StartShooting()
{
	GetWorldTimerManager().SetTimer(WeaponTimer, this, &ABasePlayerShip::Fire, ShootingSpeed, true, 0.0f);
}

void ABasePlayerShip::StopShooting()
{
	GetWorldTimerManager().ClearTimer(WeaponTimer);
}

void ABasePlayerShip::StartShootingSpecialWeapon()
{
	if (!GetWorldTimerManager().IsTimerActive(SpecialWeaponTimer))
	{
		SpecLaserCoolDown = 20.0f;
		FireSpecial();
		GetWorldTimerManager().SetTimer(SpecialWeaponTimer, this, &ABasePlayerShip::CooldownPassing,  1.0f, true, 0.0f);
	}
}

void ABasePlayerShip::StopShootingSpecialWeapon()
{
	GetWorldTimerManager().ClearTimer(SpecialWeaponTimer);
}
// ///////////////////////////Shooting&Firing/////////////////////////////////////////////////////////////////////////////////////////////

void ABasePlayerShip::FirePhysical(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World)
{
	APhysicalProjectile* Projectile = World->SpawnActor<APhysicalProjectile>(PlayerLocation, PlayerRotation);
	if (Projectile)
	{
		FVector LaunchDirection{ PlayerRotation.Vector() };
		Projectile->FireInDirection(LaunchDirection, MoveSpeed);
	}
}

void ABasePlayerShip::FireLaser(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World)
{	
	
	ALaserProjectile* Projectile = World->SpawnActor<ALaserProjectile>(PlayerLocation, PlayerRotation);
	if (Projectile)
	{
		FVector LaunchDirection{ PlayerRotation.Vector() };
		Projectile->FireInDirection(LaunchDirection, MoveSpeed);
	}
}

void ABasePlayerShip::FirePlasma(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World)
{
	APlasmaProjectile* Projectile = World->SpawnActor<APlasmaProjectile>(PlayerLocation, PlayerRotation);
	if (Projectile)
	{
		FVector LaunchDirection{ PlayerRotation.Vector() };
		Projectile->FireInDirection(LaunchDirection, MoveSpeed);
	}
}

void ABasePlayerShip::FireSpecLaser(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World)
{
	ABigLaserSpecial* SpecLaser = World->SpawnActor<ABigLaserSpecial>(PlayerLocation, PlayerRotation);
	if (SpecLaser)
	{
		//SpecLaser->SetActorRotation({ 0.0f, 0.0f, 90.0f });
		SpecLaser->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BigLaserSpecSocket");
		SpecLaser->SpecLaserMeshComponent->SetRelativeScale3D({ 4.0f, 1.0f, 1.0f });
	}
}

void ABasePlayerShip::FireNuclearSpecial(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World)
{
	ANuclearRocketSpecial* SpecNuclear = World->SpawnActor<ANuclearRocketSpecial>(PlayerLocation, PlayerRotation);
	if (SpecNuclear)
	{
		FVector LaunchDirection{ PlayerRotation.Vector() };
		SpecNuclear->FireInDirection(LaunchDirection, MoveSpeed);
	}
}

void ABasePlayerShip::FireSmallSpecial(const FVector& PlayerLocation, const FRotator& PlayerRotation, UWorld* World)
{
	FVector StartingLocation{ PlayerLocation.X, PlayerLocation.Y - 375.0f, PlayerLocation.Z };
	for (int i{ 0 }; i < 6; ++i)
	{
		ASmallRocketsSpecial* SpecSmall = World->SpawnActor<ASmallRocketsSpecial>(StartingLocation, PlayerRotation);
		if (SpecSmall)
		{
			FVector LaunchDirection{ PlayerRotation.Vector() };
			SpecSmall->FireInDirection(LaunchDirection, MoveSpeed);
		}
		StartingLocation.Y += 150.0f;
	}
}

void ABasePlayerShip::Fire()
{
	FRotator PlayerRotation{ GetActorRotation() };
	FVector PlayerLocation{ GetActorLocation() + PlayerRotation.RotateVector(GunOffset) };
	PlayerLocation.X += FiringModification;
	UWorld* World = GetWorld();
	if (World)
	{
		//FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this;
		//SpawnParams.Instigator = GetInstigator();
		switch (InventorySystem->MainWeapon)
		{
		case 0:	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, TEXT("No weapon")); break;
		case 1: FirePhysical(PlayerLocation, PlayerRotation, World); break;
		case 2: FireLaser(PlayerLocation, PlayerRotation, World); break;
		case 3: FirePlasma(PlayerLocation, PlayerRotation, World); break;
		default: break;
		}
	}
}

void ABasePlayerShip::FireSpecial()
{
	FRotator PlayerRotation{ GetActorRotation() };
	FVector PlayerLocation{ GetActorLocation() + PlayerRotation.RotateVector(SpecialGunOffset) };
	PlayerLocation.X += FiringModification;
	UWorld* World = GetWorld();
	if (World)
	{
		switch (InventorySystem->SpecialWeapon)
		{
		case 0: GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("No special weapon")); break;
		case 1: FireSpecLaser(PlayerLocation, PlayerRotation, World); break;
		case 2: FireNuclearSpecial(PlayerLocation, PlayerRotation, World); break;
		case 3: FireSmallSpecial(PlayerLocation, PlayerRotation, World); break;
		default: break;
		}
	}
}

void ABasePlayerShip::Interaction()
{
	FVector PlayerLocation{ GetActorLocation() };
	UWorld* World = GetWorld();
	if (World)
	{
		TArray<AActor*> ObjectsInRange;
		ShipActivationRange->GetOverlappingActors(ObjectsInRange);
		for (int i{ 0 }; i < ObjectsInRange.Num(); ++i)
		{
			ABasePlanet* BasePlanet = Cast<ABasePlanet>(ObjectsInRange[i]);
			AMapChanger* MapChanger = Cast<AMapChanger>(ObjectsInRange[i]);
			if (BasePlanet)
			{
				GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, TEXT("Planet"));
				BasePlanet->bIsActivated = true;
			}
			if (MapChanger)
			{
				GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, TEXT("MapChanger"));
				ChangeLevel();
			}
		}
	}
}

// Called every frame
void ABasePlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	FString CurrentLevel = World->GetMapName();

	USpaceGameInstance* SpaceGameInstance = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::Printf(TEXT("%lld"), InventorySystem->ProjectileAmmo));

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	//Find rotation value
	const float RotationValue = GetInputAxisValue(RotateRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	FHitResult Hit(1.f);

	if (CurrentLevel == "UEDPIE_0_NewWorld")
	{
		// If non-zero size, move this actor
		if (Movement.SizeSquared() > 0.0f)
		{
			const FRotator NewRotation = Movement.Rotation();
			RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

			if (Hit.IsValidBlockingHit())
			{
				const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
				const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
				RootComponent->MoveComponent(Deflection, NewRotation, true);
			}
		}
	}
	else
	{
		const FRotator NewRotation = GetActorRotation();
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		if (!CurrentRotation.IsZero())
		{
			FRotator NewRotator = CurrentRotation * DeltaTime;
			FQuat NewQuaternion = FQuat(NewRotator);
			AddActorLocalRotation(NewQuaternion);
		}
	}

}