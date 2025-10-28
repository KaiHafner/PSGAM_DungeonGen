#include "DungeonGenerator.h"
#include "Rooms/Room1.h"
#include "MasterRoom.h"
#include "Components/BoxComponent.h"
#include "MasterClosingWall.h"
#include "Rooms/BossRoom.h"
#include "Kismet/GameplayStatics.h"

ADungeonGenerator::ADungeonGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();

	SetSeed();
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

	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, ClosingUnusedExitList);
	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, Exits);
}

void ADungeonGenerator::SpawnNextRoom()
{
	bCanSpawn = true;

	if (RoomLimit <= 0)
	{
		bDungeonCompleted = true;
		return;
	}

	if (RoomLimit % 10 == 0)
	{
		if (SpecialSpawnRooms.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("SpecialSpawnRooms is empty!"));
			return;
		}

		int32 SpecialRoomIndex = RandomStream.RandRange(0, SpecialSpawnRooms.Num() - 1);
		LatestSpawnedRoom = GetWorld()->SpawnActor<AMasterRoom>(SpecialSpawnRooms[SpecialRoomIndex]);
	}
	else
	{
		if (RoomsToBeSpawned.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("RoomsToBeSpawned is empty!"));
			return;
		}

		int32 RoomIndex = RandomStream.RandRange(0, RoomsToBeSpawned.Num() - 1);
		LatestSpawnedRoom = GetWorld()->SpawnActor<AMasterRoom>(RoomsToBeSpawned[RoomIndex]);
	}

	if (Exits.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No exits available! Exits array is empty."));
		return;
	}

	int32 ExitIndex = RandomStream.RandRange(0, Exits.Num() - 1);
	SelectedExitPoint = Exits[ExitIndex];

	SpawnedRooms.Add(LatestSpawnedRoom);

	if (LinearDungeon) 
	{
		Exits.Empty();
	}

	LatestSpawnedRoom->SetActorLocation(SelectedExitPoint->GetComponentLocation());
	LatestSpawnedRoom->SetActorRotation(SelectedExitPoint->GetComponentRotation());

	RemoveOverlappingRooms();
	
	if (bCanSpawn)
	{
		LatestSpawnedRoom->GetExitHolder()->GetChildrenComponents(false, LatestRoomClosingExit);
		ClosingUnusedExitList.Append(LatestRoomClosingExit);
		ClosingUnusedExitList.Remove(SelectedExitPoint);

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
	else
	{
		bDungeonCompleted = true;
		SpawnBossRoom();
		CloseExits();
	}
}

void ADungeonGenerator::RemoveOverlappingRooms()
{
	TArray<USceneComponent*> OverlappedRooms;
	LatestSpawnedRoom->OverlapHolder->GetChildrenComponents(false, OverlappedRooms);

	//TArray<UPrimitiveComponent*> OverlappingRooms;
	for(USceneComponent* Element : OverlappedRooms)
	{
		/*Cast<UBoxComponent>(Element)->GetOverlappingComponents(OverlappingRooms);*/
		
		for (AMasterRoom* Room : SpawnedRooms) 
		{
			if (Cast<UBoxComponent>(Element)->IsOverlappingActor(Room))
			{
				RoomLimit = RoomLimit + 1;
				bCanSpawn = false;
				LatestSpawnedRoom->Destroy();

				if (LinearDungeon) 
				{
					RestartDungeon();
				}
			}
		}
	}

	//for (UPrimitiveComponent* Element : OverlappingRooms)
	//{
	//	bCanSpawn = false;
	//	RoomLimit = RoomLimit + 1;
	//	LatestSpawnedRoom->Destroy();
	//}
}

void ADungeonGenerator::CloseExits()
{
	for (USceneComponent* Element : ClosingUnusedExitList) 
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

void ADungeonGenerator::SpawnBossRoom()
{
	if (LatestSpawnedRoom && LatestSpawnedRoom->GetExitHolder())
	{
		TArray<USceneComponent*> LastRoomExits;
		LatestSpawnedRoom->GetExitHolder()->GetChildrenComponents(false, LastRoomExits);

		for (USceneComponent* Exit : LastRoomExits)
		{
			ClosingUnusedExitList.Remove(Exit);
		}
	}

	ABossRoom* BossRoom = GetWorld()->SpawnActor<ABossRoom>(BossRoomToBeSpawned);
	BossRoom->SetActorLocation(SelectedExitPoint->GetComponentLocation());
	BossRoom->SetActorRotation(SelectedExitPoint->GetComponentRotation());

	if (LatestSpawnedRoom)
	{
		LatestSpawnedRoom->Destroy();
	}
}


void ADungeonGenerator::RestartDungeon()
{
	FName CurrentLevel = GetWorld()->GetFName();
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevel);
}

