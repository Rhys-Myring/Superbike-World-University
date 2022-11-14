// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward class declaration
class UHUDWidget;

/**
 * 
 */
class FMP_API HUDManager
{
private:
	
	FText*		m_bestLapTimeText;	// Stores the best lap time text
	UHUDWidget* m_pHUDWidget;		// Stores the widget that shows the lap times to the player
	FText*		m_lapTimeText;		// Stores the Lap time text

public:
	// Constructor
	HUDManager( UWorld* world );

	// Destructor
	~HUDManager();

	// Hides the HUD from the screen and deletes the widget
	void removeFromScreen();

	// Updates the text that displays the best lap time
	void setBestLapTimeText( float bestLapTimeText );

	// Updates the text that displays the current lap time
	void setLapTimeText( float lapTime );
};
