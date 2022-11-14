// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameClass.generated.h"

// Forward Class declarations
enum class GameStates;
class AGameplayInputHandler;
class AMenuInputHandler;
class LoadingManager;
class MenuManager;
class TimeTrialMode;
class UAudioComponent;
class UDataTable;
class USoundCue;
class UUserWidget;

/**
 *
 */
UCLASS()
class FMP_API AMainGameClass : public AGameModeBase
{
	GENERATED_BODY()

private:
	UUserWidget*			m_pBackgroundVideo;			// Stores the video that's played in the background
	GameStates*				m_pCurrentGameState;		// Stores the current game state
	AGameplayInputHandler*	m_pGameplayInputHandler;	// Stores the Gameplay Input Handler
	float					m_globalVolume;				// Stores the global volume for the game
	bool					m_isGhostEnabled;			// Stores whether the ghost is enabled or not
	bool					m_isSoundMuted;				// Stores whether the sounds are muted or not
	LoadingManager*			m_pLoadingManager;			// Stores the loading manager
	UUserWidget*			m_pLoadingScreen;			// Stores the loading screen
	float					m_loadingTimer;				// Stores the elapsed time since a track has loaded
	UAudioComponent*		m_pMainMenuAudioComponent;	// Stores the Menu Music audio component
	AMenuInputHandler*		m_pMenuInputHandler;		// Stores the Menu Input Handler
	MenuManager*			m_pMenuManager;				// Stores the menu manager
	FString*				m_pSelectedBike;			// Stores which bike has been selected
	FString*				m_pSelectedTrack;			// Stores which track has been selected
	TimeTrialMode*			m_pTimeTrialMode;			// Stores the time trial mode object

	UPROPERTY( EditAnywhere, Category = "DataTables", meta = ( DisplayName = "Bikes DataTable" ) )
	UDataTable* m_pBikesDataTable;	// Stores a datatable that contains all of the bikes that exist in the game

	UPROPERTY( EditAnywhere, Category = "DataTables", meta = ( DisplayName = "Sounds DataTable" ) )
	UDataTable* m_pSoundsDataTable;	// Stores a datatable that contains all of the ui sounds that exist in the game

	UPROPERTY( EditAnywhere, Category = "DataTables", meta = ( DisplayName = "Tracks DataTable" ) )
	UDataTable* m_pTracksDataTable;	// Stores a datatable that contains all of the tracks that exist in the game

	UPROPERTY( EditAnywhere, Category = "DataTables", meta = ( DisplayName = "Widgets DataTable" ) )
	UDataTable* m_pWidgetsDataTable;	// Stores a datatable that contains all of the widgets that exist in the game

	// Mutes or unmutes all sound based on the current muted value
	void muteToggleAllSounds();

	// Carries out certain functions based on which state is being entered
	void onStateEnter( GameStates newstate );

	// Carries out certain functions based on which state is being exited
	void onStateExit();

	// Sets up the background video widget
	void setupBackgroundVideo();

	// Sets up the loading screen widget
	void setupLoadingScreen();

	// Sets up the menu input handler
	void setupMenuInputHandler();

	// Sets up the menu music object
	void setupMenuMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Constructor
	AMainGameClass();

	// Destructor
	~AMainGameClass();

	// Returns a reference to the menu manager
	MenuManager* getMenuManager();

	// Getters
	const float getGlobalVolume() const;
	const bool getIsGhostEnabled() const;
	const bool getIsSoundMuted() const;
	const UDataTable* getBikesDT() const;
	const UDataTable* getSoundsDT() const;
	const UDataTable* getTracksDT() const;
	const UDataTable* getWidgetsDT() const;

	// Setters
	void setIsGhostEnabled( bool enabled );
	void setIsSoundMuted( bool muted );
	void setSelectedBike( FString selectedBike );
	void setSelectedTrack( FString selectedTrack );

	// Pauses the game
	void pauseGame();

	// Unpauses the game
	void unPauseGame();

	// Returns the game to the main menu
	void returnToMenu();

	// Sets the current game state
	void setGameState( GameStates newState );

	// Sorts out objects before shutdown to prevent any crashes
	void safeExitGame();

	// Starts the time trial mode with the given settings
	void startTimeTrialMode();

	// Called every frame
	virtual void Tick( float deltaTime ) override;
};