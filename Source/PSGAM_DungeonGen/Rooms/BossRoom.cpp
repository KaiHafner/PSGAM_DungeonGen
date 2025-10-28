// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRoom.h"

ABossRoom::ABossRoom()
{
	EndPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndPoint"));
	EndPoint->SetupAttachment(GeometryHolder);

}
