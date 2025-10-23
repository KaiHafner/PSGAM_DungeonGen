// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MasterRoom.h"
#include "Room1.generated.h"

/**
 * 
 */
UCLASS()
class PSGAM_DUNGEONGEN_API ARoom1 : public AMasterRoom
{
	GENERATED_BODY()

public:
	ARoom1();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow1;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow2;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow3;
	
};
