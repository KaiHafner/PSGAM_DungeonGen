#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class ARoom1;
class AMasterRoom;
class AMasterClosingWall;
class ABossRoom;
UCLASS()
class PSGAM_DUNGEONGEN_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ADungeonGenerator();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<ARoom1> StartingRoom;

	//Array of all possible rooms that can be stored
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<AMasterRoom>> RoomsToBeSpawned;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<AMasterRoom>> SpecialSpawnRooms;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<ABossRoom> BossRoomToBeSpawned;


	UPROPERTY(EditAnywhere, Category = "Unused Exits Closing Wall")
	TSubclassOf<AMasterClosingWall> ClosingWall;

	UPROPERTY(EditAnywhere, Category = "Generation Info")
	int32 RoomLimit;

	UPROPERTY(EditAnywhere, Category = "Generation Info")
	bool LinearDungeon;

	//Seed stuff
	FRandomStream RandomStream;
	UPROPERTY(EditAnywhere, Category = "Generation Info")
	int32 GenerationSeed; //If -1 in engine random seed

	//Roomn spawning Info
	AMasterRoom* LatestSpawnedRoom;
	bool bCanSpawn;

	USceneComponent* SelectedExitPoint;

	TArray<USceneComponent*>Exits;

	TArray<AMasterRoom*> SpawnedRooms;

	TArray<USceneComponent*> ClosingUnusedExitList;
	TArray<USceneComponent*> LatestRoomClosingExit;

	bool bDungeonCompleted;


	void SpawnStartingRoom();
	void SpawnNextRoom();
	void RemoveOverlappingRooms();
	void CloseExits();
	void SetSeed();
	void SpawnBossRoom();
	void RestartDungeon();

protected:
	virtual void BeginPlay() override;


};
