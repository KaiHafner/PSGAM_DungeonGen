// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MasterRoom.h"
#include "Room2.generated.h"

/**
 * 
 */
UCLASS()
class PSGAM_DUNGEONGEN_API ARoom2 : public AMasterRoom
{
	GENERATED_BODY()
	
	ARoom2();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow1;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow2;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Closing_Wall1;
};
