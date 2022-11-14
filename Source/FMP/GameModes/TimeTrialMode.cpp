// Don't put includes on this line as it breaks intellisense

#include "TimeTrialMode.h"
#include "FMP/Bike/Bike.h"
#include "FMP/DataTables/BikeDataTableStruct.h"
#include "FMP/Ghosts/GhostManager.h"
#include "FMP/HUD/HUDManager.h"
#include "FMP/InputHandlers/GameplayInputHandler.h"
#include "FMP/LapManagement/LapManager.h"
#include "FMP/LapManagement/LapTimer.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Misc/Helpers.h"
#include "FMP/SaveSystem/SaveManager.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

// Constructor
TimeTrialMode::TimeTrialMode( AMainGameClass* mainGameObject, FString* trackName, FString* bikeName, 
	AGameplayInputHandler* inputHandler )
	: m_pCurrentBikeName( bikeName )
	, m_pCurrentTrackName( trackName )
	, m_isPaused( false )
	, m_pMainGameObject( mainGameObject )
{
	// Sets pointers to null initially
	m_pGhostManager = nullptr;
	m_pGhostMesh = nullptr;
	m_pHUDManager = nullptr;
	m_pLapManager = nullptr;
	m_pLapTimer = nullptr;
	m_pPlayerBike = nullptr;
	m_pSaveManager = nullptr;

	// Sets world pointer
	m_pCurrentWorld = m_pMainGameObject->GetWorld();

	// Sets the input handler
	m_pGameplayInputHandler = inputHandler;
}

// Destructor
TimeTrialMode::~TimeTrialMode()
{
	// Deletes all pointers to avoid any memory leaks
	safeDelete( m_pGhostManager );
	safeDelete( m_pHUDManager );
	safeDelete( m_pLapManager );
	safeDelete( m_pLapTimer );
	safeDelete( m_pSaveManager );
}

// Exits the mode and deletes any left over objects
void TimeTrialMode::exit()
{
	// Saves data
	saveData();

	// Destroys ghost bike
	m_pGhostMesh->Destroy();

	// Destroys player bike
	m_pPlayerBike->Destroy();

	// Removes HUD from screen
	m_pHUDManager->removeFromScreen();
}

// Intialises all the objects used in this class
void TimeTrialMode::initialiseObjects()
{
	// Initialises the player bike object
	initialisePlayerObject();

	// Initialises the input manager object
	initialiseInputManager();

	// Initialises the ghost bike mesh object
	initialiseGhostMeshObject();

	// Creates Save manager
	m_pSaveManager = new SaveManager( m_pCurrentTrackName );

	// Initialises the ghost manager object
	initialiseGhostManager();

	// Initialises the lap manager object
	initialiseLapManager();

	// Initialises the heads up display manager object
	initialiseHUDManager();
}

// Initialises the ghost manager object
void TimeTrialMode::initialiseGhostManager()
{
	// Creates ghost manager
	m_pGhostManager = new GhostManager();

	// Sets the mesh in the ghost playback object so the mesh can be moved around to represent a ghost
	m_pGhostManager->setGhostObject( m_pGhostMesh );

	// Sets player object in ghost manager
	m_pGhostManager->setPlayerObject( m_pPlayerBike );

	// Sets the array of transforms for the ghost that is to be played
	m_pGhostManager->setGhostBeingPlayed( m_pSaveManager->getGhostTransform() );
}

// Creates the ghost bike object
void TimeTrialMode::initialiseGhostMeshObject()
{
	// Finds the ghost bike class to spawn from the data table
	TSubclassOf<AActor> ghostToSpawn = m_pMainGameObject->getBikesDT()->FindRow<FBikeDataTableStruct>
		( FName( *m_pCurrentBikeName ), "" )->BikeGhostClass.LoadSynchronous();

	// Spawns ghost mesh into the level
	m_pGhostMesh = m_pCurrentWorld->SpawnActor<AActor>( ghostToSpawn );

	// Sets the ghost mesh's visiblity based on the setting
	m_pGhostMesh->SetActorHiddenInGame( !m_pMainGameObject->getIsGhostEnabled() );
}

// Initialises the heads up display manager object
void TimeTrialMode::initialiseHUDManager()
{
	// Creates HUD manager
	m_pHUDManager = new HUDManager( m_pCurrentWorld );

	// Sets intial best lap time
	if( m_pLapTimer->getBestTime() != 0.0f )
	{
		// Updates best laptime text
		m_pHUDManager->setBestLapTimeText( m_pLapTimer->getBestTime() );
	}
}

// Initialises the input manager object
void TimeTrialMode::initialiseInputManager()
{
	// Sets the bike that's being controlled to the Player's bike
	m_pGameplayInputHandler->setBikeToControl( m_pPlayerBike );

	// Possesses the Gameplay Input Handler
	UGameplayStatics::GetPlayerController( m_pCurrentWorld, 0 )->Possess( m_pGameplayInputHandler );

	// Sets the current camera to the bike's camera
	setCameraToBike();
}

// Initialises the lap manager object
void TimeTrialMode::initialiseLapManager()
{
	// Creates lap timer
	m_pLapTimer = new LapTimer();

	// Loads best lap time for current track
	m_pLapTimer->setBestTime( m_pSaveManager->getTime() );

	// Creates lap manager
	m_pLapManager = new LapManager( m_pCurrentWorld, m_pPlayerBike );

	// Finds the checkpoint container
	m_pLapManager->findCheckPointContainer();
}

// Creates the player bike object
void TimeTrialMode::initialisePlayerObject()
{
	// Finds the player start object
	AActor* playerStartObject = UGameplayStatics::GetActorOfClass( m_pCurrentWorld, APlayerStart::StaticClass() );

	// Finds the bike class to spawn from the data table
	TSubclassOf<ABike> bikeToSpawn = m_pMainGameObject->getBikesDT()->FindRow<FBikeDataTableStruct>
		( FName( *m_pCurrentBikeName ), "" )->BikeClass.LoadSynchronous();

	// Spawns bike into the level
	m_pPlayerBike = m_pCurrentWorld->SpawnActor<ABike>( bikeToSpawn );

	// Sets bike's location and rotation to the player start
	m_pPlayerBike->SetActorLocation( playerStartObject->GetActorLocation() );
	m_pPlayerBike->SetActorRotation( playerStartObject->GetActorRotation() );

	// Sets the bike's volume
	m_pPlayerBike->setVolume( m_pMainGameObject->getGlobalVolume() );
}

// Resets the lap and ghost objects, along with storing the laptime if it has been improved
void TimeTrialMode::lapCompleted()
{
	// Resets laptimer
	m_pLapTimer->reset();

	// Sets lap to not completed
	m_pLapManager->setLapComplete( false );

	// Sets new best lap time for current track if it has changed
	if( m_pLapTimer->getHasTimeBeenBeaten() )
	{
		// Updates best laptime text
		m_pHUDManager->setBestLapTimeText( m_pLapTimer->getBestTime() );

		// Stops recording the current ghost
		m_pGhostManager->stopRecordingGhost();

		// Stores new ghost and lap time to be saved later
		m_pSaveManager->setTime( m_pLapTimer->getBestTime() );
		m_pSaveManager->setGhostTransform( m_pGhostManager->getRecordedGhostTransform() );

		// Sets time beaten to false
		m_pLapTimer->setHasTimeBeenBeaten( false );

		// Swaps the ghost arrays as the new ghost that has just been set should now be the one that is playing
		m_pGhostManager->swapGhostArrays();
	}

	// Resets the ghost playback and recording
	m_pGhostManager->resetGhosts();
}

// Saves any data on exit (Either from the game entirely or just the mode)
void TimeTrialMode::saveData()
{
	// Checks whether the data has actually changed
	if( m_pSaveManager->getHasChanged() )
	{
		// Saves the time and ghost to the save file
		m_pSaveManager->save();
	}
}

// Sets the current camera to the bike
void TimeTrialMode::setCameraToBike()
{
	// Sets the current camera to the bike's camera
	UGameplayStatics::GetPlayerController( m_pCurrentWorld, 0 )->SetViewTarget( m_pPlayerBike );
}

// Pauses/Unpauses the game
void TimeTrialMode::setPaused( bool paused )
{
	m_isPaused = paused;

	// Pauses/Unpauses the player bike
	m_pPlayerBike->pause( paused );	
}

// Update function
void TimeTrialMode::update( float deltaTime )
{
	// Runs update functions if the game is not paused
	if( !m_isPaused )
	{
		// Updates Bike Object
		m_pPlayerBike->update( deltaTime );

		// Updates Ghost Manager
		m_pGhostManager->update( deltaTime );

		// Updates Lap Manager
		m_pLapManager->update( deltaTime );

		// Updates Lap Timer
		m_pLapTimer->update( deltaTime );

		// Updates HUD laptime text
		m_pHUDManager->setLapTimeText( m_pLapTimer->getLapTime() );

		// If a lap has been completed
		if( m_pLapManager->getLapComplete() )
		{
			// Resets the ghost objects and stores the new lap time and ghost if the previous one was beaten
			lapCompleted();
		}
	}
}

