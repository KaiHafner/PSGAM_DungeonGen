#include "DungeonGenerator.h"
#include "Rooms/Room1.h"
#include "MasterRoom.h"
#include "Components/BoxComponent.h"
#include "MasterClosingWall.h"
#include "Kismet/GameplayStatics.h"

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

	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, ClosingUnusedExits);

	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, Exits);
}

void ADungeonGenerator::SpawnNextRoom()
{
	bCanSpawn = true;

	if (RoomLimit <= 0)
	{
		return;
	}
	if (Exits.Num() == 0)
	{
		return;
	}

	//RoomLimit % 10 == 0 means 1/10 rooms is special 
	if (RoomLimit % 10 == 0) 
	{
		int32 SpecialRoomIndex = RandomStream.RandRange(0, SpecialSpawnRooms.Num() - 1);
		LatestSpawnedRoom = this->GetWorld()->SpawnActor<AMasterRoom>(SpecialSpawnRooms[SpecialRoomIndex]);
	}
	else 
	{
		int32 RoomIndex = RandomStream.RandRange(0, RoomsToBeSpawned.Num() - 1);
		LatestSpawnedRoom = this->GetWorld()->SpawnActor<AMasterRoom>(RoomsToBeSpawned[RoomIndex]);
	}

	// Find the exit whose forward vector is closest to PreferredDirection
	float BestDot = -1.f;
	USceneComponent* SelectedExitPoint = nullptr;

	for (USceneComponent* Exit : Exits)
	{
		FVector ExitForward = Exit->GetForwardVector().GetSafeNormal();
		float Dot = FVector::DotProduct(ExitForward, PreferredDirection.GetSafeNormal());

		if (Dot > BestDot)
		{
			BestDot = Dot;
			SelectedExitPoint = Exit;
		}
	}

	if (RandomStream.FRand() < 0.4f) //20% random exits
	{
		SelectedExitPoint = Exits[RandomStream.RandRange(0, Exits.Num() - 1)];
	}

	//Fallback if none found
	if (!SelectedExitPoint && Exits.Num() > 0)
	{
		SelectedExitPoint = Exits[0];
	}

	if (LinearDungeon)
	{
		Exits.Empty();
	}

	LatestSpawnedRoom->SetActorLocation(SelectedExitPoint->GetComponentLocation());
	LatestSpawnedRoom->SetActorRotation(SelectedExitPoint->GetComponentRotation());

	RemoveOverlappingRooms();
	
	if (bCanSpawn)
	{
		LatestSpawnedRoom->GetExitHolder()->GetChildrenComponents(false, LatestClosingExits);
		ClosingUnusedExits.Append(LatestClosingExits);
		ClosingUnusedExits.Remove(SelectedExitPoint);

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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Dungeon Completed: %d"), GenerationSeedResult));
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

		if (LinearDungeon)
		{
			RestartGen();
		}
	}
}

void ADungeonGenerator::CloseExits()
{
	for (USceneComponent* Element : ClosingUnusedExits)
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

void ADungeonGenerator::RestartGen()
{
	FName CurrentLevel = GetWorld()->GetFName();
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevel);
}
