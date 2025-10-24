#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class ARoom1;
class AMasterRoom;
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

	UPROPERTY(EditAnywhere, Category = "Generation Info")
	int32 RoomLimit;

	AMasterRoom* LatestSpawnedRoom;
	
	bool bCanSpawn;

	TArray<USceneComponent*>Exits;

	void SpawnStartingRoom();
	void SpawnNextRoom();
	void RemoveOverlappingRooms();
	void CloseExits();

protected:
	virtual void BeginPlay() override;


};
