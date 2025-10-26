#include "DungeonGenerator.h"
#include "Rooms/Room1.h"
#include "MasterRoom.h"
#include "Components/BoxComponent.h"
#include "MasterClosingWall.h"

ADungeonGenerator::ADungeonGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle CloseWallHandler;

	SetSeed();
	SpawnStartingRoom();
	SpawnNextRoom();

	GetWorld()->GetTimerManager().SetTimer(CloseWallHandler, this, &ADungeonGenerator::CloseExits, 1.0f, false);
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

	int32 RoomIndex = RandomStream.RandRange(0, RoomsToBeSpawned.Num() - 1);
	LatestSpawnedRoom = this->GetWorld()->SpawnActor<AMasterRoom>(RoomsToBeSpawned[RoomIndex]);

	int32 ExitIndex = RandomStream.RandRange(0, Exits.Num() - 1);
	USceneComponent* SelectedExitPoint = Exits[ExitIndex];

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
		AMasterClosingWall* ClosingWallSpawned = GetWorld()->SpawnActor<AMasterClosingWall>(ClosingWall);

		//RelativeOffset sets position for wall curently flush with other walls
		FVector RelativeOffset(-50.0f, 0.0f, 250.0f);
		FVector WorldOffset = Element->GetComponentRotation().RotateVector(RelativeOffset);

		ClosingWallSpawned->SetActorLocation(Element->GetComponentLocation() + WorldOffset);
		ClosingWallSpawned->SetActorRotation(Element->GetComponentRotation());

	}
}

void ADungeonGenerator::SetSeed()
{
	int32 GenerationSeedResult;
	if (GenerationSeed == -1) 
	{
		GenerationSeedResult = FMath::Rand();
	}
	else 
	{
		GenerationSeedResult = GenerationSeed;
	}
	RandomStream.Initialize(GenerationSeedResult);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%d"), GenerationSeedResult));
}

