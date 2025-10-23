#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterRoom.generated.h"

class UBoxComponent;
class UArrowComponent;
UCLASS()
class PSGAM_DUNGEONGEN_API AMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterRoom();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE USceneComponent* GetExitHolder() const { return ExitHolder; }

protected:
	virtual void BeginPlay() override;

	//Folders
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* GeometryHolder;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* OverlapHolder;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ExitHolder;

	//Important base setup for all
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Floor;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* DirectionArrow;
};