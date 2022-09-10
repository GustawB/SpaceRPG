// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.h"
#include "PhysicalProjectile.generated.h"

UCLASS()
class SPACERPG_API APhysicalProjectile : public ABasicProjectile
{
	GENERATED_BODY()
	
public:	
	
	APhysicalProjectile(const FObjectInitializer& ObjectInitializer);

};
