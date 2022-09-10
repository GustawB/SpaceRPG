// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.h"
#include "PlasmaProjectile.generated.h"

UCLASS()
class SPACERPG_API APlasmaProjectile : public ABasicProjectile
{
	GENERATED_BODY()
	
public:	
	
	APlasmaProjectile(const FObjectInitializer& ObjectInitializer);

};
