#include "DungeonGenerator.h"
#include "Rooms/Room1.h"
#include "MasterRoom.h"
#include "Components/BoxComponent.h"

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
	bCanSpawn = true;

	LatestSpawnedRoom = this->GetWorld()->SpawnActor<AMasterRoom>(RoomsToBeSpawned[rand() % RoomsToBeSpawned.Num()]);
	USceneComponent* SelectedExitPoint = Exits[rand() % Exits.Num()];
	LatestSpawnedRoom->SetActorLocation(SelectedExitPoint->GetComponentLocation());
	LatestSpawnedRoom->SetActorRotation(SelectedExitPoint->GetComponentRotation());

	RemoveOverlappingRooms();
	
	if (bCanSpawn)
	{
		Exits.Remove(SelectedExitPoint);
		TArray<USceneComponent*> LatestExitPoints;
		LatestSpawnedRoom->GetExitHolder()->GetChildrenComponents(false, LatestExitPoints);
		Exits.Append(LatestExitPoints);
	}

	RoomLimit = RoomLimit - 1;

	if (RoomLimit > 0) 
	{
		SpawnNextRoom();
	}
}

void ADungeonGenerator::RemoveOverlappingRooms()
{
	TArray<USceneComponent*> OverlappedRooms;
	LatestSpawnedRoom->OverlapHolder->GetChildrenComponents(false, OverlappedRooms);

	TArray<UPrimitiveComponent*> OverlappingRooms;
	for(USceneComponent* Element : OverlappedRooms)
	{
		Cast<UBoxComponent>(Element)->GetOverlappingComponents(OverlappingRooms);
	}

	for (UPrimitiveComponent* Element : OverlappingRooms)
	{
		bCanSpawn = false;
		RoomLimit = RoomLimit + 1;
		LatestSpawnedRoom->Destroy();
	}
}

void ADungeonGenerator::CloseExits()
{
	for (USceneComponent* Element : Exits) 
	{

	}
}

