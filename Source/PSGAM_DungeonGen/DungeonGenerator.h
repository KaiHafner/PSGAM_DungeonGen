#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class ARoom1;
class AMasterRoom;
class AMasterClosingWall;
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


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Info")
	int32 GenerationSeedResult;

	//Roomn spawning Info
	AMasterRoom* LatestSpawnedRoom;
	bool bDungeonCompleted;
	bool bCanSpawn;

	TArray<USceneComponent*>Exits;

	TArray<USceneComponent*> ClosingUnusedExits;
	TArray<USceneComponent*> LatestClosingExits;



	void SpawnStartingRoom();
	void SpawnNextRoom();
	void RemoveOverlappingRooms();
	void CloseExits();
	void SetSeed();
	void RestartGen();

	// Inside ADungeonGenerator.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
	FVector PreferredDirection = FVector(1.f, 0.f, 0.f); // Along +X axis

protected:
	virtual void BeginPlay() override;


};
