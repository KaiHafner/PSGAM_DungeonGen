// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MasterRoom.h"
#include "Hallway1.generated.h"

/**
 * 
 */
UCLASS()
class PSGAM_DUNGEONGEN_API AHallway1 : public AMasterRoom
{
	GENERATED_BODY()

public:
	AHallway1();
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow1;
};
