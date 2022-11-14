// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingManager.h"
#include "Engine/LevelStreaming.h"
#include "FMP/GameStates/GameStates.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "Kismet/GameplayStatics.h"

// Constructor
LoadingManager::LoadingManager( AMainGameClass* mainGameMode )
{
	// Intialises map being loaded string
	m_pMapBeingLoaded = new FName();

	// Stores a reference to the main game mode so it's state can be modified
	m_pMainGameMode = mainGameMode;
}

// Destructor
LoadingManager::~LoadingManager()
{
}

// Loads a given map
void LoadingManager::LoadMap( FString* mapToLoad )
{
	// Sets the name of the map being loaded
	*m_pMapBeingLoaded = FName( *mapToLoad );

	// If the map isn't already loaded in, loads the map
	if( !UGameplayStatics::GetStreamingLevel( m_pMainGameMode, *m_pMapBeingLoaded )->IsLevelLoaded() )
	{
		// Loads given map
		UGameplayStatics::LoadStreamLevel( m_pMainGameMode, *m_pMapBeingLoaded, true, true, FLatentActionInfo() );

		// Sets game state to loading
		m_pMainGameMode->setGameState( GameStates::Loading );
	}
}

// Unloads a given map
void LoadingManager::UnloadMap( FString* mapToUnLoad )
{
	bool test = UGameplayStatics::GetStreamingLevel( m_pMainGameMode, FName( *mapToUnLoad ) )->IsLevelLoaded();

	// If the map is loaded in, unloads the map
	if( UGameplayStatics::GetStreamingLevel( m_pMainGameMode, FName( *mapToUnLoad ) )->IsLevelLoaded() )
	{
		// Unloads given map
		UGameplayStatics::UnloadStreamLevel( m_pMainGameMode, FName( *mapToUnLoad ), FLatentActionInfo(), false );
	}
}

// Returns whether the map being loaded is complete
bool LoadingManager::isLoadComplete()
{
	// Checks there is a map currently being loaded
	if( m_pMapBeingLoaded != nullptr )
	{
		return UGameplayStatics::GetStreamingLevel( m_pMainGameMode, *m_pMapBeingLoaded )->IsLevelLoaded();
	}
	else
	{
		return false;
	}
}
