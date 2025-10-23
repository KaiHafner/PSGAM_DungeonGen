#include "DungeonGenerator.h"
#include "Rooms/Room1.h"
#include "MasterRoom.h"

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
	ARoom1* SpawnedStartRoom = this->GetWorld()->SpawnActor<ARoom1>(StartingRoom);
	SpawnedStartRoom->SetActorLocation(this->GetActorLocation());

	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, Exits);
}

void ADungeonGenerator::SpawnNextRoom()
{
	AMasterRoom* LatestSpawnedRoom = this->GetWorld()->SpawnActor<AMasterRoom>(RoomsToBeSpawned[rand() % RoomsToBeSpawned.Num()]);
	USceneComponent* SelectedExitPoint = Exits[rand() % Exits.Num()];
	LatestSpawnedRoom->SetActorLocation(SelectedExitPoint->GetComponentLocation());
	LatestSpawnedRoom->SetActorRotation(SelectedExitPoint->GetComponentRotation());
}

