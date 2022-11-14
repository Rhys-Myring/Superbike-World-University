// Don't put includes on this line it causes issues

#include "CheckPointContainer.h"
#include "Engine/TriggerBox.h"
#include "FMP/Bike/Bike.h"

// Sets default values
ACheckPointContainer::ACheckPointContainer()
{
 	// Set this actor to not Tick() every frame
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACheckPointContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPointContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Getter so other objects can access the checkpoints
const ATriggerBox* ACheckPointContainer::getCheckPoint( int index ) const
{
	return m_checkPoints[index];
}

// Getter so other objects can access the array of checkpoints
const TArray<ATriggerBox*>* ACheckPointContainer::getCheckPointArray() const
{
	return &m_checkPoints;
}

