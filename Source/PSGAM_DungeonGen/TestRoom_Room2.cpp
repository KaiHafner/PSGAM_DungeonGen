// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRoom_Room2.h"
#include "Components/ArrowComponent.h"

ATestRoom_Room2::ATestRoom_Room2() 
{
	Exit_Arrow1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow1"));
	Exit_Arrow2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Exit_Arrow2"));
	Closing_Wall1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Closing_Wall1"));

	Exit_Arrow1->SetupAttachment(ExitHolder);
	Exit_Arrow2->SetupAttachment(ExitHolder);
	Closing_Wall1->SetupAttachment(ExitHolder);
}