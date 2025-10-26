// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterClosingWall.generated.h"

UCLASS()
class PSGAM_DUNGEONGEN_API AMasterClosingWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterClosingWall();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ClosingWall;

};
