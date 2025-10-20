// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterRoom.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMasterRoom::AMasterRoom()
{
	PrimaryActorTick.bCanEverTick = true;

	//Sorting Folder Stuff
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	GeometryHolder = CreateDefaultSubobject<USceneComponent>(TEXT("GeometryHolder"));
	OverlapHolder = CreateDefaultSubobject<USceneComponent>(TEXT("OverlapHolder"));

	//Cubes
	Cube_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_1"));
	Cube_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_2"));
	Cube_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_3"));
	Cube_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_4"));
	Cube_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_5"));
	Cube_6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_6"));
	Cube_7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_7"));
	Cube_8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_8"));

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_Collision"));

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction_Arrow"));

	DefaultSceneRoot->SetupAttachment(RootComponent);

	GeometryHolder->SetupAttachment(DefaultSceneRoot);
	OverlapHolder->SetupAttachment(DefaultSceneRoot);
	DirectionArrow->SetupAttachment(DefaultSceneRoot);

	Cube_1->SetupAttachment(GeometryHolder);
	Cube_2->SetupAttachment(GeometryHolder);
	Cube_3->SetupAttachment(GeometryHolder);
	Cube_4->SetupAttachment(GeometryHolder);
	Cube_5->SetupAttachment(GeometryHolder);
	Cube_6->SetupAttachment(GeometryHolder);
	Cube_7->SetupAttachment(GeometryHolder);
	Cube_8->SetupAttachment(GeometryHolder);
	Floor->SetupAttachment(GeometryHolder);

	BoxCollision->SetupAttachment(OverlapHolder);

	DirectionArrow->bHiddenInGame = false;
}

void AMasterRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

