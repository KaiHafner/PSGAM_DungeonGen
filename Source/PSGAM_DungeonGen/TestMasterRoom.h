// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestMasterRoom.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class PSGAM_DUNGEONGEN_API ATestMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestMasterRoom();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	//Creating Folders
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* GeometryHolder;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* OverlapHolder;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ExitHolder;


	//For Meshes
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Floor;


	//Collision Boxes
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* DirectionArrow;
};
