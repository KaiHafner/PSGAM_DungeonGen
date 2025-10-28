// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MasterRoom.h"
#include "BossRoom.generated.h"

/**
 * %
 */
UCLASS()
class PSGAM_DUNGEONGEN_API ABossRoom : public AMasterRoom
{
	GENERATED_BODY()

protected:

	ABossRoom();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* EndPoint;

};
