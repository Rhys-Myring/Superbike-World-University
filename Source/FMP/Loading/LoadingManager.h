// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward class declaration
class AMainGameClass;
class FName;

/**
 * 
 */
class FMP_API LoadingManager
{
private:
	AMainGameClass*		m_pMainGameMode;		// Stores reference to main game mode so it's state can be modified
	FName*				m_pMapBeingLoaded;		// Stores the name of the track that's currently being loaded

public:
	// Constructor
	LoadingManager( AMainGameClass* mainGameMode );
	
	// Destructor
	~LoadingManager();

	// Loads a given map
	void LoadMap( FString* mapToLoad );

	// Unloads a given map
	void UnloadMap( FString* mapToUnLoad );

	// Returns whether the map being loaded is complete
	bool isLoadComplete();
};
