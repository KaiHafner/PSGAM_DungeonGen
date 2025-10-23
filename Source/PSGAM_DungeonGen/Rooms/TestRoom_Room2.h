// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TestMasterRoom.h"
#include "TestRoom_Room2.generated.h"

/**
 * 
 */
UCLASS()
class PSGAM_DUNGEONGEN_API ATestRoom_Room2 : public ATestMasterRoom
{
	GENERATED_BODY()
	
	ATestRoom_Room2();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow1;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* Exit_Arrow2;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Closing_Wall1;
};
