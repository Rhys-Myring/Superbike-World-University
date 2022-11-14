// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward Class Declaration
class AActor;

/**
 *
 */
class FMP_API GhostPlayback
{
private:
	TArray<FTransform>* m_pGhostBeingPlayed;	// Array to store the transforms of the ghost at a set interval
	int					m_ghostIndex;			// Stores which index in the array is currently being interpolated towards
	AActor*				m_pGhostObject;			// Stores the object that will have its positions set
	float				m_timer;				// Stores how much time has passed since the last set time interval

	// Lerps the Ghost's position and rotation towards the next stored point
	void lerpToNextTransform( FTransform* start, FTransform* end );

public:
	// Constructor
	GhostPlayback();

	// Destructor
	~GhostPlayback();

	// Setters
	void setGhostBeingPlayed( TArray<FTransform>* ghostPlayback );
	void setGhostObject( AActor* ghostObject );

	// Getter
	TArray<FTransform>* getGhostBeingPlayed();

	// Restarts the playback of the current ghost
	void restart();

	// Update function
	void update( float deltaTime );
};
