// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward class declarations
class AActor;
class ACheckPointContainer;
class UWorld;

/**
 * 
 */
class FMP_API LapManager
{

private:
	ACheckPointContainer*	m_pCheckPointContainer;			// Stores the checkpoint container for the current track
	int						m_numberOfCheckPoints;			// Stores the number of checkpoints in the current track
	AActor*					m_pPlayer;						// Stores the player object
	int						m_playerCurrentCheckPointIndex; // Stores the index of the current checkpoint the player is in
	bool					m_hasLapBeenCompleted;			// Stores whether a lap has been completed or not
	UWorld*					m_pWorld;						// Stores a pointer to the world

public:
	// Constructor
	LapManager( UWorld* world, AActor* playerObject );

	// Destructor
	~LapManager();

	// Setter
	void setLapComplete( bool isComplete );

	// Getter
	bool getLapComplete();

	// Gets the checkpoint container within the current map so the checkpoints can be accessed
	void findCheckPointContainer();

	// Update loop
	void update( float deltaTime );
};
