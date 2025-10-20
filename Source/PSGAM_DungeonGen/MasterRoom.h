// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterRoom.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class PSGAM_DUNGEONGEN_API AMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterRoom();

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


	//For Meshes
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_1;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_2;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_3;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_4;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_5;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_6;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_7;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Cube_8;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Floor;


	//Collision Boxes
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* DirectionArrow;

};
