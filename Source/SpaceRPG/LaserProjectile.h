// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.h"
#include "LaserProjectile.generated.h"

UCLASS()
class SPACERPG_API ALaserProjectile : public ABasicProjectile
{
	GENERATED_BODY()

public:	

	ALaserProjectile(const FObjectInitializer& ObjectInitializer);
};
