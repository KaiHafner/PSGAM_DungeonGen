// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterClosingWall.h"

AMasterClosingWall::AMasterClosingWall()
{
	PrimaryActorTick.bCanEverTick = true;

	ClosingWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClosingWall"));

	ClosingWall->SetupAttachment(RootComponent);

}

void AMasterClosingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterClosingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

