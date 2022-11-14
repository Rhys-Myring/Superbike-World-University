// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"
#include "GenericPlatform/GenericPlatformMisc.h"

// Constructor
UMainMenuWidget::UMainMenuWidget( const FObjectInitializer& ObjectInitializer ) :UBaseVerticalMenuWidget( ObjectInitializer )
{
}

// Destructor
UMainMenuWidget::~UMainMenuWidget()
{
}

// Loads new menu based on the selected option
void UMainMenuWidget::selectCurrentOption()
{
	switch( m_currentlySelectedIndex )
	{
		// If the time trial button is clicked
		case 0:
			// Sets menu to the time trial menu
			m_pMenuManager->setMenuScreen( MenuScreen::TimeTrial );
			break;

		// If the options button is clicked
		case 1:
			// Sets menu to the options menu
			m_pMenuManager->setMenuScreen( MenuScreen::Options );
			break;

		// If the exit game button is clicked
		case 2:
			// Exits game
			FGenericPlatformMisc::RequestExit( false );
			break;

		default:
			break;
	}
}

// Closes game as the Start page is the first page in the menu system
void UMainMenuWidget::back()
{
	// Exits game
	FGenericPlatformMisc::RequestExit( false );
}