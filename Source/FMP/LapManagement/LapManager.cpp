// Don't put includes on this line it causes issues


#include "LapManager.h"
#include "FMP/Bike/Bike.h"
#include "CheckPointContainer.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Constructor
LapManager::LapManager( UWorld* world, AActor* playerObject )
	: m_hasLapBeenCompleted( false )
	, m_numberOfCheckPoints( 0 )
	, m_playerCurrentCheckPointIndex( 0 )
{
	// Sets checkpoint container pointer to null on creation
	m_pCheckPointContainer = nullptr;
	
	// Sets the player pointer
	m_pPlayer = playerObject;

	// Sets world pointer
	m_pWorld = world;
}

// Destructor
LapManager::~LapManager()
{
}

// Setter
void LapManager::setLapComplete( bool isComplete )
{
	// Sets has lap been completed to the parameter passed in
	m_hasLapBeenCompleted = isComplete;
}

// Getter
bool LapManager::getLapComplete()
{
	return m_hasLapBeenCompleted;
}

// Gets the checkpoint container within the current map so the checkpoints can be accessed
void LapManager::findCheckPointContainer()
{
	// Searches the world for the checkpoint container to track where the checkpoints are
	AActor* actorToFind = UGameplayStatics::GetActorOfClass( m_pWorld, ACheckPointContainer::StaticClass() );

	// Casts the returned pointer to the CheckPoint container pointer as that's the class of the object being searched
	m_pCheckPointContainer = static_cast<ACheckPointContainer*>( actorToFind );

	// Sets number of checkpoints based on the object that has been found
	m_numberOfCheckPoints = m_pCheckPointContainer->getCheckPointArray()->Num();
}

// Update loop
void LapManager::update( float deltaTime )
{
	// Checks whether there are any objects inside the checkpoint array
	if( m_numberOfCheckPoints > 0 )
	{
		// Checks whether the player is inside the next checkpoint
		if( m_pCheckPointContainer->getCheckPoint( ( m_playerCurrentCheckPointIndex + 1 )
			% m_numberOfCheckPoints )->IsOverlappingActor( m_pPlayer ) )
		{
			// Increases player's checkpoint number if they have passed through the checkpoint
			m_playerCurrentCheckPointIndex++;

			// Checks whether the player has crossed the finish line
			if( m_playerCurrentCheckPointIndex % m_numberOfCheckPoints == 0 )
			{
				// Sets lap to complete
				m_hasLapBeenCompleted = true;
			}
		}
	}
}
