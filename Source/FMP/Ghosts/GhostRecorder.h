// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward Class Declaration
class AActor;

/**
 *
 */
class FMP_API GhostRecorder
{
private:
	bool				m_isRecording;		// Tells the class whether to record the ghost
	AActor*				m_pPlayerObject;	// Stores the player object to get its position
	TArray<FTransform>* m_pPlayerPositions;	// Stores the transforms of the player at set intervals
	float				m_timer;			// Keeps track of the time that has elapsed since the last time interval

public:
	// Constructor
	GhostRecorder();

	// Destructor
	~GhostRecorder();

	// Update function
	void update( float deltaTime );

	// Getter
	TArray<FTransform>* getRecordedGhostTransform();

	// Setters
	void setRecordedGhostTransform( TArray<FTransform>* newArray );
	void setPlayerObject( AActor* playerObject );

	// Stops the ghost recording
	void startRecording();

	// Stops the ghost from recording
	void stopRecording();
};