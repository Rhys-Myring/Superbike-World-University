// Don't put includes on this line as it breaks intellisense

#include "MainGameClass.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Engine/DataTable.h"
#include "FMP/DataTables/SoundsDataTableStruct.h"
#include "FMP/DataTables/WidgetDataTableStruct.h"
#include "FMP/GameModes/TimeTrialMode.h"
#include "FMP/GameStates/GameStates.h"
#include "FMP/InputHandlers/GameplayInputHandler.h"
#include "FMP/InputHandlers/MenuInputHandler.h"
#include "FMP/Loading/LoadingManager.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"
#include "FMP/Misc/Constants.h"
#include "FMP/Misc/Helpers.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "SafeShutDownGameInstance.h"

// Constructor
AMainGameClass::AMainGameClass()
	: m_globalVolume( k_defaultVolume )
	, m_isGhostEnabled( true )
	, m_isSoundMuted( false )
	, m_loadingTimer( 0.0f )
{
	// Sets background video to null by default
	m_pBackgroundVideo = nullptr;

	// Sets bikes datatable to null initially
	m_pBikesDataTable = nullptr;

	// Sets initial game state
	m_pCurrentGameState = new GameStates();
	*m_pCurrentGameState = GameStates::Menu;

	// Creates loading manager
	m_pLoadingManager = new LoadingManager( this );

	// Sets loading screen pointer to null initially
	m_pLoadingScreen = nullptr;

	// Creates main menu audio component
	m_pMainMenuAudioComponent = CreateDefaultSubobject<UAudioComponent>( "Main Menu Audio Component" );

	// Sets sounds datatable to null initially
	m_pSoundsDataTable = nullptr;

	// Initialises Menu Manager
	m_pMenuManager = new MenuManager( this );

	// Creates selected Bike String
	m_pSelectedBike = new FString();

	// Creates selected Track String
	m_pSelectedTrack = new FString();

	// Sets time trial mode pointer to null initially
	m_pTimeTrialMode = nullptr;

	// Sets tracks datatable to null initially
	m_pTracksDataTable = nullptr;

	// Sets widgets datatable to null initially
	m_pWidgetsDataTable = nullptr;

	// Sets default pawn to null
	DefaultPawnClass = nullptr;

	// Set this actor to Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

// Destructor
AMainGameClass::~AMainGameClass()
{
	// Deletes all non unreal pointers to avoid any memory leaks
	safeDelete( m_pCurrentGameState );
	safeDelete( m_pLoadingManager );
	safeDelete( m_pMenuManager );
	safeDelete( m_pSelectedBike );
	safeDelete( m_pSelectedTrack );
	safeDelete( m_pTimeTrialMode );
}

// Called when the game starts
void AMainGameClass::BeginPlay()
{
	Super::BeginPlay();

	// Sets the main game mode reference in the current game instance
	static_cast<USafeShutDownGameInstance*>(
		UGameplayStatics::GetGameInstance( GetWorld() ) )->setMainGameModeReference( this );

	// Sets the selected bike to the first one in the datatable
	*m_pSelectedBike = m_pBikesDataTable->GetRowNames()[0].ToString();

	// Sets the selected track to the first one in the datatable
	*m_pSelectedTrack = m_pTracksDataTable->GetRowNames()[0].ToString();

	// Sets up the menu input handler
	setupMenuInputHandler();

	// Creates and intialises all widgets for the menu manager
	m_pMenuManager->setUpWidgets();

	// Sets up the background video widget
	setupBackgroundVideo();

	// Sets up the loading screen widget
	setupLoadingScreen();

	// Sets up the menu music object
	setupMenuMusic();
}

// Returns a reference to the menu manager
MenuManager* AMainGameClass::getMenuManager()
{
	return m_pMenuManager;
}

// Getters
const float AMainGameClass::getGlobalVolume() const
{
	return m_globalVolume;
}

const bool AMainGameClass::getIsGhostEnabled() const
{
	return m_isGhostEnabled;
}

const bool AMainGameClass::getIsSoundMuted() const
{
	return m_isSoundMuted;
}

const UDataTable* AMainGameClass::getBikesDT() const
{
	return m_pBikesDataTable;
}

const UDataTable* AMainGameClass::getSoundsDT() const
{
	return m_pSoundsDataTable;
}

const UDataTable* AMainGameClass::getTracksDT() const
{
	return m_pTracksDataTable;
}

const UDataTable* AMainGameClass::getWidgetsDT() const
{
	return m_pWidgetsDataTable;
}

// Setters
void AMainGameClass::setIsGhostEnabled( bool enabled )
{
	m_isGhostEnabled = enabled;
}

void AMainGameClass::setIsSoundMuted( bool muted )
{
	m_isSoundMuted = muted;

	// Sets all sounds to either muted or unmuted
	muteToggleAllSounds();
}

void AMainGameClass::setSelectedBike( FString selectedBike )
{
	*m_pSelectedBike = selectedBike;
}

void AMainGameClass::setSelectedTrack( FString selectedTrack )
{
	*m_pSelectedTrack = selectedTrack;
}

// Mutes or unmutes all sound based on the current muted value
void AMainGameClass::muteToggleAllSounds()
{
	// If sound is muted
	if( m_isSoundMuted )
	{
		// Sets global volume to 0
		m_globalVolume = 0.0f;

	}
	// If sound is unmuted
	else
	{
		// Sets global volume to 1
		m_globalVolume = 1.0f;
	}
	
	// Sets Music volume
	m_pMainMenuAudioComponent->SetVolumeMultiplier( m_globalVolume );
}

// Sets up the background video widget
void AMainGameClass::setupBackgroundVideo()
{
	// Creates background video
	m_pBackgroundVideo = CreateWidget<UUserWidget>( GetWorld(),
		m_pWidgetsDataTable->FindRow<FWidgetDataTableStruct>( k_backgroundVideo, "" )->Widget.LoadSynchronous() );

	// Adds background video to root so it doesn't get deleted by the garbage collector
	m_pBackgroundVideo->AddToRoot();

	// Adds background video to viewport
	m_pBackgroundVideo->AddToViewport( k_backgroundVideoZOrder );
}

// Sets up the loading screen widget
void AMainGameClass::setupLoadingScreen()
{
	// Creates loading screen
	m_pLoadingScreen = CreateWidget<UUserWidget>( GetWorld(),
		m_pWidgetsDataTable->FindRow<FWidgetDataTableStruct>( k_loadingScreen, "" )->Widget.LoadSynchronous() );

	// Adds loading screen to root so it doesn't get deleted by the garbage collector
	m_pLoadingScreen->AddToRoot();
}

// Sets up the menu input handler
void AMainGameClass::setupMenuInputHandler()
{
	// Spawns the Menu Input Handler into the world
	m_pMenuInputHandler = GetWorld()->SpawnActor<AMenuInputHandler>( AMenuInputHandler::StaticClass() );

	// Possesses the Menu Input Handler
	UGameplayStatics::GetPlayerController( GetWorld(), 0 )->Possess( m_pMenuInputHandler );
}

// Sets up the menu music object
void AMainGameClass::setupMenuMusic()
{
	// Sets the main menu music
	m_pMainMenuAudioComponent->SetSound( m_pSoundsDataTable->FindRow<FSoundsDataTableStruct>( "MainMenuMusic", "" )->Sound );

	// Starts playing main menu music
	m_pMainMenuAudioComponent->Play();
}

// Pauses the game
void AMainGameClass::pauseGame()
{
	// Possesses the Menu Input Handler
	UGameplayStatics::GetPlayerController( GetWorld(), 0 )->Possess( m_pMenuInputHandler );

	// Keeps the camera pointing at the bike
	m_pTimeTrialMode->setCameraToBike();
	
	// Sets the current menu screen to the pause menu
	m_pMenuManager->setMenuScreen( MenuScreen::Pause );

	// Sets game to paused
	m_pTimeTrialMode->setPaused( true );
}

// Unpauses the game
void AMainGameClass::unPauseGame()
{	
	// Possesses the Gameplay Input Handler
	UGameplayStatics::GetPlayerController( GetWorld(), 0 )->Possess( m_pGameplayInputHandler );

	// Keeps the camera pointing at the bike
	m_pTimeTrialMode->setCameraToBike();

	// Hides the menu
	m_pMenuManager->hideMenu();

	// Sets game to unpaused
	m_pTimeTrialMode->setPaused( false );
}

// Returns the game to the main menu
void AMainGameClass::returnToMenu()
{
	// Saves all data and cleans up the Time Trial mode object
	m_pTimeTrialMode->exit();

	// Deletes the Time Trial mode object
	safeDelete( m_pTimeTrialMode );
	
	// Destroys the gameplay input handler
	m_pGameplayInputHandler->Destroy();

	// Sets gameplay input handler to null
	m_pGameplayInputHandler = nullptr;

	// Sets the current menu screen to the main menu
	m_pMenuManager->setMenuScreen( MenuScreen::MainMenu );

	// Unloads the current track
	m_pLoadingManager->UnloadMap( m_pSelectedTrack );

	// Sets the game state to the menu
	setGameState( GameStates::Menu );
}

// Sets the current game state
void AMainGameClass::setGameState( GameStates newState )
{
	// Carries out function based on the state being entered
	onStateEnter( newState );

	// Carries out function based on the state being exited
	onStateExit();

	// Sets the new game state
	*m_pCurrentGameState = newState;
}

// Carries out certain functions based on which state is being entered
void AMainGameClass::onStateEnter( GameStates newstate )
{
	// Switch based on the given game state
	switch( newstate )
	{
		// If state being entered is the menu
		case GameStates::Menu:

			// Adds background video to viewport
			m_pBackgroundVideo->AddToViewport( k_backgroundVideoZOrder );

			// Starts playing main menu music
			m_pMainMenuAudioComponent->Play();

			break;

		// If state being entered is gameplay
		case GameStates::Gameplay:
			break;

		// If state being entered is loading
		case GameStates::Loading:

			// Displays loading screen
			m_pLoadingScreen->AddToViewport( k_loadingScreenZOrder );

			// Hides the menu
			m_pMenuManager->hideMenu();

			break;

		// If state being entered is finalise loading
		case GameStates::FinaliseLoading:
			break;

		// If state being entered is invalid
		default:

			// Exits game safely to avoid any issues caused by the invalid state
			FGenericPlatformMisc::RequestExit( false );

			break;
	}
}

// Carries out certain functions based on which state is being exited
void AMainGameClass::onStateExit()
{
	// Switch based on the game state
	switch( *m_pCurrentGameState )
	{
		// If state being exited is the menu
		case GameStates::Menu:

			// Removes background video from viewport
			m_pBackgroundVideo->RemoveFromViewport();

			// Stops playing main menu music
			m_pMainMenuAudioComponent->Stop();

		// If state being exited is gameplay
		case GameStates::Gameplay:
			break;

		// If state being exited is loading
		case GameStates::Loading:
			break;

		// If state being exited is finalise loading
		case GameStates::FinaliseLoading:

			// Removes loading screen from the screen
			m_pLoadingScreen->RemoveFromViewport();

			// Resets loading timer
			m_loadingTimer = 0.0f;

			break;

		// If state being exited is invalid
		default:

			// Exits game safely to avoid any issues caused by the invalid state
			FGenericPlatformMisc::RequestExit( false );

			break;
	}
}

// Sorts out objects before shutdown to prevent any crashes
void AMainGameClass::safeExitGame()
{
	// Sets background video to be non-rooted
	m_pBackgroundVideo->RemoveFromRoot();

	// Sets loading screen to be non-rooted
	m_pLoadingScreen->RemoveFromRoot();

	// Sets any rooted widgets to not rooted so they can be destroyed
	m_pMenuManager->unrootAllWidgets();

	// If the current game mode is gameplay, any unsaved progress is saved
	if( *m_pCurrentGameState == GameStates::Gameplay )
	{
		m_pTimeTrialMode->saveData();
	}
}

// Starts the time trial mode with the given settings
void AMainGameClass::startTimeTrialMode()
{
	// Starts loading the map for the time trial mode
	m_pLoadingManager->LoadMap( m_pSelectedTrack );

	// Spawns the gameplay input handler into the world
	m_pGameplayInputHandler = GetWorld()->SpawnActor<AGameplayInputHandler>( AGameplayInputHandler::StaticClass() );

	// Creates new time trial mode object
	m_pTimeTrialMode = new TimeTrialMode( this, m_pSelectedTrack, m_pSelectedBike, m_pGameplayInputHandler );
}

// Called every frame
void AMainGameClass::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	switch( *m_pCurrentGameState )
	{
		// If the game is in the menu
		case GameStates::Menu:

			// Updates the menu manager
			m_pMenuManager->update();

			break;

		// If the game is loading
		case GameStates::Loading:

			// If the map loading is complete, initialises the time trial mode and sets state to finalise loading
			if( m_pLoadingManager->isLoadComplete() )
			{
				// Initialises the time trial object
				m_pTimeTrialMode->initialiseObjects();

				// Sets game state to finalise loading
				setGameState( GameStates::FinaliseLoading );
			}

			break;

		// If the game is finalising loading
		case GameStates::FinaliseLoading:

			// Waits 3 seconds to allow all the textures to load in before changing to the gameplay state
			if( m_loadingTimer >= k_extraLoadingTime )
			{
				// Sets game state to gameplay
				setGameState( GameStates::Gameplay );
			}

			// Increases loading timer
			m_loadingTimer += deltaTime;

			break;

		// If the game is in the gameplay mode
		case GameStates::Gameplay:

			// Updates the time trial mode
			m_pTimeTrialMode->update( deltaTime );

			break;

		// Default in case the state is invalid
		default:

			// Exits game safely to avoid any issues caused by the invalid state
			FGenericPlatformMisc::RequestExit( false );

			break;
	}
}