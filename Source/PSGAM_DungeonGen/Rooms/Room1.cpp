// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1.h"
#include "Components/ArrowComponent.h"

ARoom1::ARoom1()
{
	//Creates Arrows (Exit + Close)
	Exit_Arrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow1"));
	Exit_Arrow2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow2"));
	Exit_Arrow3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow3"));

	//Attaches to Foldering
	Exit_Arrow1->SetupAttachment(ExitHolder);
	Exit_Arrow2->SetupAttachment(ExitHolder);
	Exit_Arrow3->SetupAttachment(ExitHolder);

	//Show in game
	Exit_Arrow1->bHiddenInGame = false;
	Exit_Arrow2->bHiddenInGame = false;
	Exit_Arrow3->bHiddenInGame = false;
}
