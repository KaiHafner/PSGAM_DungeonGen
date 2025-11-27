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

	//Generation Info
	UPROPERTY(EditAnywhere, Category = "Generation Info")
	int32 RoomLimit;

	UPROPERTY(EditAnywhere, Category = "Generation Info", meta = (ToolTip = "RoomLimit % StairFrequency "))
	int32 StairFrequency;


	FRandomStream RandomStream;
	UPROPERTY(EditAnywhere, Category = "Generation Info")
	int32 GenerationSeed; //-1 = random seed

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Info")
	int32 GenerationSeedResult;

	UPROPERTY(EditAnywhere, Category = "Generation Info")
	bool LinearDungeon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Info")
	bool bDungeonCompleted;

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
