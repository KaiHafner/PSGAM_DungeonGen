#include "DungeonGenerator.h"
#include "TestRoom_Room1.h"


ADungeonGenerator::ADungeonGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnStartingRoom();
}

void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::SpawnStartingRoom()
{
	ATestRoom_Room1* SpawnedStartRoom = this->GetWorld()->SpawnActor<ATestRoom_Room1>(StartingRoom);
	SpawnedStartRoom->SetActorLocation(this->GetActorLocation());
}

