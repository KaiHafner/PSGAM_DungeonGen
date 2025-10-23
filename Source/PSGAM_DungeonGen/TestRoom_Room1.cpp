// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRoom_Room1.h"
#include "Components/ArrowComponent.h"

ATestRoom_Room1::ATestRoom_Room1()
{
	Exit_Arrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow1"));
	Exit_Arrow2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow2"));
	Exit_Arrow3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow3"));

	Exit_Arrow1->SetupAttachment(ExitHolder);
	Exit_Arrow2->SetupAttachment(ExitHolder);
	Exit_Arrow3->SetupAttachment(ExitHolder);

	Exit_Arrow1->bHiddenInGame = false;
	Exit_Arrow2->bHiddenInGame = false;
	Exit_Arrow3->bHiddenInGame = false;
}
