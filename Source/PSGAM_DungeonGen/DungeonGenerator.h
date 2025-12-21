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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FRandomStream RandomStream;

	//Generation Info
	UPROPERTY(EditAnywhere, Category = "Generation Info")
	int32 GenerationSeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generation Info")
	int32 GenerationSeedResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation Info")
	bool bDungeonCompleted;


	//Generation Settings
	UPROPERTY(EditAnywhere, Category = "Generation Settings")
	int32 RoomLimit;

	UPROPERTY(EditAnywhere, Category = "Generation Settings")
	int32 MinRoomsBetweenStairs = 3;
	int32 RoomsSinceLastStair = 0;

	UPROPERTY(EditAnywhere, Category = "Generation Settings")
	bool LinearDungeon;

	UPROPERTY(EditAnywhere, Category = "Generation Settings")
	bool AllowStairways;


	//Rooms
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<ARoom1> StartingRoom;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<AMasterRoom>> RoomsToBeSpawned;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<AMasterRoom>> Stairways;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<AMasterRoom>> BossRoom;

	UPROPERTY(EditAnywhere, Category = "Closing Wall")
	TSubclassOf<AMasterClosingWall> ClosingWall;

	void SpawnStartingRoom();
	void SpawnNextRoom();
	void RemoveOverlappingRooms();
	void CloseExits();
	void SetSeed();
	void SpawnBossRoom();
	void SoftRestartGen();

	bool IsRoomOverlap(AMasterRoom* RoomToCheck);

protected:
	UPROPERTY()
	TArray<AActor*> SpawnedActors;

	TArray<USceneComponent*>Exits;
	TArray<USceneComponent*> ClosingUnusedExits;
	TArray<USceneComponent*> LatestClosingExits;

	AMasterRoom* LatestSpawnedRoom;

	bool bCanSpawn;
	int32 TotalAttempts = 0;
	int32 StartingRoomLimit;
};
