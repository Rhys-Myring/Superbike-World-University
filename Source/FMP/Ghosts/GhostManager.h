// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward Class Declaration
class AActor;
class GhostPlayback;
class GhostRecorder;

/**
 * 
 */
class FMP_API GhostManager
{
private:
	TArray<FTransform>* m_pBestGhost;		// Stores the array of transforms used by the currently fastest ghost
	GhostPlayback*		m_pGhostPlayback;	// Stores the ghost playback object that plays the current ghost
	GhostRecorder*		m_pGhostRecorder;	// Stores the ghost recorder object that records the player's position

public:
	// Constructor
	GhostManager();

	// Destructor
	~GhostManager();

	// Getter
	TArray<FTransform>* getRecordedGhostTransform();

	// Setters
	void setPlayerObject( AActor* playerObject );
	void setGhostBeingPlayed( TArray<FTransform>* ghostPlayback );
	void setGhostObject( AActor* ghostObject );

	// Stops the ghost recording
	void startRecordingGhost();

	// Stops the ghost from recording
	void stopRecordingGhost();

	// Resets the ghosts that are being recorded and played back
	void resetGhosts();

	// Swaps the array being recorded and the array being played back
	void swapGhostArrays();

	// Update function
	void update( float deltaTime );
};
