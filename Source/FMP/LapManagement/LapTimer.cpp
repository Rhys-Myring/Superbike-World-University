// Fill out your copyright notice in the Description page of Project Settings.


#include "LapTimer.h"

// Constructor
LapTimer::LapTimer()
	: m_bestLapTime( 0.0f )
	, m_lapTime( 0.0f )
	, m_hasTimeBeenBeaten( false )
{
}

// Destructor
LapTimer::~LapTimer()
{
}

// Getters
float LapTimer::getLapTime()
{
	return m_lapTime;
}

float LapTimer::getBestTime()
{
	return m_bestLapTime;
}

bool LapTimer::getHasTimeBeenBeaten()
{
	return m_hasTimeBeenBeaten;
}

// Setters
void LapTimer::setLapTime( float lapTime )
{
	m_lapTime = lapTime;
}

void LapTimer::setBestTime( float bestTime )
{
	m_bestLapTime = bestTime;
}

void LapTimer::setHasTimeBeenBeaten( bool beaten )
{
	m_hasTimeBeenBeaten = beaten;
}

// Checks whether the completed time is the new best or not
void LapTimer::checkIfNewBestTime()
{
	// If new best time is set, it is stored in the best time variable and time is set to beaten
	if( m_bestLapTime == 0.0f || m_bestLapTime > m_lapTime )
	{
		m_bestLapTime = m_lapTime;
		m_hasTimeBeenBeaten = true;
	}
}

// Starts timer by setting it to 0
void LapTimer::start()
{
	// Sets laptime to 0
	m_lapTime = 0.0f;
}


// Resets timer to 0 and checks whether the completed lap was an improvement
void LapTimer::reset()
{
	// Checks whether the new time is better than the one currently stored
	checkIfNewBestTime();

	// Starts timer
	start();
}

// Update Function
void LapTimer::update( float deltaTime )
{
	// Increases timer
	m_lapTime += deltaTime;
}
