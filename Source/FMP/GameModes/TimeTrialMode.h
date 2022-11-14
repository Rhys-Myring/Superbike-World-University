// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward Class declarations
class ABike;
class AGameplayInputHandler;
class AMainGameClass;
class GhostManager;
class HUDManager;
class LapManager;
class LapTimer;
class SaveManager;
class UWorld;

/**
 *
 */
class FMP_API TimeTrialMode
{
private:
	FString*				m_pCurrentBikeName;			// Stores the name of the current bike
	FString*				m_pCurrentTrackName;		// Stores the name of the current track
	UWorld*					m_pCurrentWorld;			// Stores a pointer to the current level
	AGameplayInputHandler*	m_pGameplayInputHandler;	// Stores a pointer to the Gameplay Input Handler
	GhostManager*			m_pGhostManager;			// Stores the Ghost manager
	AActor*					m_pGhostMesh;				// Stores the ghost mesh object ghost BP class
	HUDManager*				m_pHUDManager;				// Stores the HUD Manager
	bool					m_isPaused;					// Stores whether the game is paused
	LapManager*				m_pLapManager;				// Stores the Lap manager
	LapTimer*				m_pLapTimer;				// Stores the Lap timer
	AMainGameClass*			m_pMainGameObject;			// Stores a reference to the main game object
	ABike*					m_pPlayerBike;				// Stores the player bike object
	SaveManager*			m_pSaveManager;				// Stores the Save manager

	// Initialises the ghost manager object
	void initialiseGhostManager();

	// Creates the ghost bike object
	void initialiseGhostMeshObject();

	// Initialises the heads up display manager object
	void initialiseHUDManager();

	// Initialises the input manager object
	void initialiseInputManager();

	// Creates the lap manager object
	void initialiseLapManager();

	// Creates the player bike object
	void initialisePlayerObject();

	// Resets the lap and ghost objects, along with storing the laptime if it has been improved
	void lapCompleted();

public:
	// Constructor
	TimeTrialMode( AMainGameClass* mainGameObject, FString* trackName, FString* bikeName, AGameplayInputHandler* inputHandler  );

	// Destructor
	~TimeTrialMode();

	// Exits the mode and deletes any left over objects
	void exit();

	// Intialises all the objects used in this class
	void initialiseObjects();

	// Saves any data on exit (Either from the game entirely or just the mode)
	void saveData();

	// Sets the current camera to the bike
	void setCameraToBike();

	// Pauses/Unpauses the game
	void setPaused( bool paused );

	// Updates function
	void update( float deltaTime );
};
