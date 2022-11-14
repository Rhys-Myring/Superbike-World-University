// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "FMP/MainGameClasses/MainGameClass.h"

// Constructor
UPauseMenuWidget::UPauseMenuWidget( const FObjectInitializer& ObjectInitializer ) :UBaseVerticalMenuWidget( ObjectInitializer )
{
}

// Destructor
UPauseMenuWidget::~UPauseMenuWidget()
{
}

// Sets the paused state or returns the player to the menu based on what option is selected 
void UPauseMenuWidget::selectCurrentOption()
{
	switch( m_currentlySelectedIndex )
	{
		// If the resume button is clicked
		case 0:

			// Tells the base game mode to unpause the game
			static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() )->unPauseGame();
			
			break;

		// If the return to main menu button is clicked
		case 1:

			// Tells the base game mode to return to the main menu
			static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() )->returnToMenu();
			
			break;

		// If option is invalid does nothing
		default:
			break;
	}
}

// Unpauses the game
void UPauseMenuWidget::back()
{
	// Tells the base game mode to unpause the game
	static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() )->unPauseGame();
}