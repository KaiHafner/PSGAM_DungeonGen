#include "MasterRoom.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AMasterRoom::AMasterRoom()
{
	PrimaryActorTick.bCanEverTick = true;

	//Sorting Folder Stuff
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	GeometryHolder = CreateDefaultSubobject<USceneComponent>(TEXT("GeometryHolder"));
	OverlapHolder = CreateDefaultSubobject<USceneComponent>(TEXT("OverlapHolder"));
	ExitHolder = CreateDefaultSubobject<USceneComponent>(TEXT("ExitHolder"));

	//Creating Base Geometry and Collision for each room
	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_Collision"));
	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction_Arrow"));

	//Organize into created folders
	DefaultSceneRoot->SetupAttachment(RootComponent);
	GeometryHolder->SetupAttachment(DefaultSceneRoot);
	OverlapHolder->SetupAttachment(DefaultSceneRoot);
	DirectionArrow->SetupAttachment(DefaultSceneRoot);
	ExitHolder->SetupAttachment(DefaultSceneRoot);
	Floor->SetupAttachment(GeometryHolder);
	BoxCollision->SetupAttachment(OverlapHolder);

	DirectionArrow->bHiddenInGame = false;
}

void AMasterRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

