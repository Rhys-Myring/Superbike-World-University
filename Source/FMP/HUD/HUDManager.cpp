// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDManager.h"
#include "FMP/Misc/Constants.h"
#include "FMP/Misc/Helpers.h"
#include "HUDWidget.h"

// Constructor
HUDManager::HUDManager( UWorld* world )
{
	// Sets up initial best lap time text
	m_bestLapTimeText = new FText();
	*m_bestLapTimeText = FText::FromString( FString( k_defaultBestLapText ) );

	// Sets up initial current lap time text
	m_lapTimeText = new FText();
	*m_lapTimeText = FText::FromString( FString( k_defaultLapText ) );

	// Creates heads up display widget
	m_pHUDWidget = CreateWidget<UHUDWidget>( world,
		getBPClass( k_headUpDisplayPath ).LoadSynchronous() );

	// Adds heads up display to the viewport
	m_pHUDWidget->AddToViewport();

	// Sets the widget's text
	m_pHUDWidget->setBestTimeText( m_bestLapTimeText );
	m_pHUDWidget->setLapTimeText( m_lapTimeText );
}

// Destructor
HUDManager::~HUDManager()
{
}

// Hides the HUD from the screen and deletes the widget
void HUDManager::removeFromScreen()
{
	// Removes widget from viewport
	m_pHUDWidget->RemoveFromViewport();

	// Destroys the widget
	m_pHUDWidget->Destruct();

	// Sets pointer to null
	m_pHUDWidget = nullptr;
}

// Updates the text that displays the best lap time
void HUDManager::setBestLapTimeText( float bestLapTime )
{
	// Sets the best lap text
	*m_bestLapTimeText = FText::FromString( FString( "Best Time: " + convertToTimeFormattedString( bestLapTime ) ) );

	// Sets the widget's best lap text
	m_pHUDWidget->setBestTimeText( m_bestLapTimeText );
}

// Updates the text that displays the current lap time
void HUDManager::setLapTimeText( float lapTime )
{
	// Sets the current lap text
	*m_lapTimeText = FText::FromString( FString( "Time: " + convertToTimeFormattedString( lapTime ) ) );

	// Sets the widget's current lap text
	m_pHUDWidget->setLapTimeText( m_lapTimeText );
}
