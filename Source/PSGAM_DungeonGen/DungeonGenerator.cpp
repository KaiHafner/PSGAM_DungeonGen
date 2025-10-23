#include "DungeonGenerator.h"
#include "Rooms/TestRoom_Room1.h"
#include "TestMasterRoom.h"

ADungeonGenerator::ADungeonGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnStartingRoom();
	SpawnNextRoom();
}

void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::SpawnStartingRoom()
{
	ATestRoom_Room1* SpawnedStartRoom = this->GetWorld()->SpawnActor<ATestRoom_Room1>(StartingRoom);
	SpawnedStartRoom->SetActorLocation(this->GetActorLocation());

	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, Exits);
}

void ADungeonGenerator::SpawnNextRoom()
{
	ATestMasterRoom* LatestSpawnedRoom = this->GetWorld()->SpawnActor<ATestMasterRoom>(RoomsToBeSpawned[rand() % RoomsToBeSpawned.Num()]);
	USceneComponent* SelectedExitPoint = Exits[rand() % Exits.Num()];
	LatestSpawnedRoom->SetActorLocation(SelectedExitPoint->GetComponentLocation());
	LatestSpawnedRoom->SetActorRotation(SelectedExitPoint->GetComponentRotation());
}

