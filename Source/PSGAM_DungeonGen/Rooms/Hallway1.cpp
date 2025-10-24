// Fill out your copyright notice in the Description page of Project Settings.


#include "Hallway1.h"
#include "Components/ArrowComponent.h"

AHallway1::AHallway1()
{
	//Creates Arrows (Exit + Close)
	Exit_Arrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow1"));

	//Attaches to Foldering
	Exit_Arrow1->SetupAttachment(ExitHolder);

	//Show in game
	Exit_Arrow1->bHiddenInGame = false;
}
