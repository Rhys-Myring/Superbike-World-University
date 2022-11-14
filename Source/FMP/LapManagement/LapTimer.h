// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FMP_API LapTimer
{
public:
	// Constructor
	LapTimer();

	// Destructor
	~LapTimer();

	// Getters
	float getLapTime();
	float getBestTime();
	bool getHasTimeBeenBeaten();

	// Setters
	void setLapTime( float lapTime );
	void setBestTime( float bestTime );
	void setHasTimeBeenBeaten( bool beaten );

	// Resets timer to 0
	void reset();

	// Update Function
	void update( float deltaTime );

private:
	float	m_bestLapTime;			// Stores the best time
	bool	m_hasTimeBeenBeaten;	// Stores whether the best time has been beaten
	float	m_lapTime;				// Stores the current time

	// Checks whether the completed time is the new best or not
	void checkIfNewBestTime();

	// Starts timer
	void start();
};
