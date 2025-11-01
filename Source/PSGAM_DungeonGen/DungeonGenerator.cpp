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

    StartingRoomLimit = RoomLimit;

    SetSeed(); //Initialise the random seed
	SpawnStartingRoom();
	SpawnNextRoom(); //Recursive generation process (talk about this kai)
}

void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADungeonGenerator::SpawnStartingRoom()
{
    //Spawn starting room at the generator position
	ARoom1* SpawnedStartRoom = this->GetWorld()->SpawnActor<ARoom1>(StartingRoom);
	SpawnedStartRoom->SetActorLocation(this->GetActorLocation());


    SpawnedActors.Add(SpawnedStartRoom);


    //Get all the needed exits and closing points
	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, ClosingUnusedExits);
	SpawnedStartRoom->GetExitHolder()->GetChildrenComponents(false, Exits);
}

void ADungeonGenerator::SpawnNextRoom()
{
    //IMPORTANT - stop condition (no rooms left to spawn or no exits available)
    if (RoomLimit <= 0 || Exits.Num() == 0)
    {
        bDungeonCompleted = true;
        CloseExits();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
            FString::Printf(TEXT("Dungeon Completed: %d"), GenerationSeedResult));
        return;
    }

    bool bRoomPlaced = false;
    int32 RetryCount = 0;
    const int32 MaxRetries = 10;

    TotalAttempts++; //Attempt Tracker


    while (!bRoomPlaced && RetryCount < MaxRetries)
    {
        RetryCount++;

        //Pick room type
        AMasterRoom* RoomToSpawn = nullptr;
        if (RoomLimit % 10 == 0 && SpecialSpawnRooms.Num() > 0)
        {
            //Spawns special room
            int32 SpecialRoomIndex = RandomStream.RandRange(0, SpecialSpawnRooms.Num() - 1);
            RoomToSpawn = GetWorld()->SpawnActor<AMasterRoom>(SpecialSpawnRooms[SpecialRoomIndex]);
        }
        else if (RoomsToBeSpawned.Num() > 0)
        {
            //spawns normal rooms
            int32 RoomIndex = RandomStream.RandRange(0, RoomsToBeSpawned.Num() - 1);
            RoomToSpawn = GetWorld()->SpawnActor<AMasterRoom>(RoomsToBeSpawned[RoomIndex]);
        }

        if (!RoomToSpawn)
            continue;

        //Pick exit to attach to
        int32 ExitIndex = RandomStream.RandRange(0, Exits.Num() - 1);
        USceneComponent* SelectedExit = Exits[ExitIndex];

        //Position and rotate the new room to the exit
        RoomToSpawn->SetActorLocation(SelectedExit->GetComponentLocation());
        RoomToSpawn->SetActorRotation(SelectedExit->GetComponentRotation());

        //Check if it actually doees overlap with existing geometry
        if (IsRoomOverlap(RoomToSpawn))
        {
            RoomToSpawn->Destroy();
            continue;
        }

        //Placement success
        LatestSpawnedRoom = RoomToSpawn;
        bRoomPlaced = true;



        SpawnedActors.Add(RoomToSpawn);



        //Update exit lists
        TArray<USceneComponent*> LatestExitPoints;
        LatestSpawnedRoom->GetExitHolder()->GetChildrenComponents(false, LatestExitPoints);

        //Control Linear VS Non Linear
        if (LinearDungeon)
        {
            Exits.Empty();
        }
        else
        {
            Exits.Remove(SelectedExit);
        }

        Exits.Append(LatestExitPoints);

        //Update closing walls list
        LatestSpawnedRoom->GetExitHolder()->GetChildrenComponents(false, LatestClosingExits);
        ClosingUnusedExits.Append(LatestClosingExits);
        ClosingUnusedExits.Remove(SelectedExit);

        RoomLimit--;
    }

    //If still failed after all retries, restart the level
    if (!bRoomPlaced)
    {
        GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, FString::Printf(TEXT("Failed to place room after %d retries. Restarting with new seed..."), MaxRetries));

        SoftRestartGen();
        //RestartGen();
        return;
    }

    //Continue generation
    if (RoomLimit > 0)
    {
        SpawnNextRoom();
    }
    else
    {
        bDungeonCompleted = true;
        CloseExits();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Dungeon Completed: %d (Attempts: %d)"), GenerationSeedResult, TotalAttempts));
    }
}

bool ADungeonGenerator::IsRoomOverlap(AMasterRoom* RoomToCheck)
{
    TArray<USceneComponent*> OverlapCheckComponents;
    RoomToCheck->OverlapHolder->GetChildrenComponents(false, OverlapCheckComponents);

    for (USceneComponent* Component : OverlapCheckComponents)
    {
        TArray<UPrimitiveComponent*> OverlappingComps;
        Cast<UBoxComponent>(Component)->GetOverlappingComponents(OverlappingComps);
        if (OverlappingComps.Num() > 0)
        {
            return true;
        }
    }
    return false;
}

void ADungeonGenerator::RemoveOverlappingRooms()
{
	TArray<USceneComponent*> OverlappedRooms;
	LatestSpawnedRoom->OverlapHolder->GetChildrenComponents(false, OverlappedRooms);

	TArray<UPrimitiveComponent*> OverlappingRooms;
	for (USceneComponent* Element : OverlappedRooms)
	{
		Cast<UBoxComponent>(Element)->GetOverlappingComponents(OverlappingRooms);
	}

	for (UPrimitiveComponent* Element : OverlappingRooms)
	{
		bCanSpawn = false;
		RoomLimit = RoomLimit + 1;

		if (IsValid(LatestSpawnedRoom))
		{
			LatestSpawnedRoom->Destroy();
		}

        
        //RestartGen();
        return;
	}
}

void ADungeonGenerator::CloseExits()
{
	for (USceneComponent* Element : ClosingUnusedExits)
	{
        //Spawn actor at unused wall
		AMasterClosingWall* ClosingWallSpawned = GetWorld()->SpawnActor<AMasterClosingWall>(ClosingWall);


        SpawnedActors.Add(ClosingWallSpawned);



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

void ADungeonGenerator::SoftRestartGen()
{
    for (AActor* Spawned : SpawnedActors)
    {
        if (IsValid(Spawned))
        {
            Spawned->Destroy();
        }
    }

    SpawnedActors.Empty();
    Exits.Empty();
    ClosingUnusedExits.Empty();
    LatestClosingExits.Empty();
    LatestSpawnedRoom = nullptr;
    TotalAttempts = 0;

    RoomLimit = StartingRoomLimit;
    SetSeed();
    SpawnStartingRoom();
    SpawnNextRoom();
}