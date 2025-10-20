#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"


class ATestRoom_Room1;
class ATestMasterRoom;
UCLASS()
class PSGAM_DUNGEONGEN_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ADungeonGenerator();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<ATestRoom_Room1> StartingRoom;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<ATestMasterRoom> RoomsToBeSpawned;

	void SpawnStartingRoom();

protected:
	virtual void BeginPlay() override;


};
