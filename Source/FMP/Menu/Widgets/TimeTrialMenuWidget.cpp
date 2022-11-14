// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrialMenuWidget.h"
#include "Components/TextBlock.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"
#include "FMP/Misc/Constants.h"

// Constructor
UTimeTrialMenuWidget::UTimeTrialMenuWidget( const FObjectInitializer& ObjectInitializer ) 
	:UBaseVerticalMenuWidget( ObjectInitializer )
{
	// Sets enable ghost text to null by default
	EnableGhostText = nullptr;
}

// Destructor
UTimeTrialMenuWidget::~UTimeTrialMenuWidget()
{
}

// Loads new menu based on the selected option
void UTimeTrialMenuWidget::selectCurrentOption()
{
	switch( m_currentlySelectedIndex )
	{
		// If the start time trial button is clicked
		case 0:

			// Tells the base game mode to start time trial
			static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() )->startTimeTrialMode();
			
			break;

		// If the select bike button is clicked
		case 1:

			// Sets menu to the select bike menu
			m_pMenuManager->setMenuScreen( MenuScreen::SelectBike );
			
			break;

		// If the select track button is clicked
		case 2:

			// Sets menu to the select track menu
			m_pMenuManager->setMenuScreen( MenuScreen::SelectTrack );
			
			break;

		// If the enable ghost button is clicked
		case 3:
			
			// Sets the ghost enabled variable to true or false and alters the text to match
			toggleGhostEnabled();
			
			break;

		// If option is invalid does nothing
		default:
			break;
	}
}

// Returns to the main menu as that is the previous menu before the time trial one
void UTimeTrialMenuWidget::back()
{
	// Sets menu to the main menu
	m_pMenuManager->setMenuScreen( MenuScreen::MainMenu );
}

// Sets the ghost enabled variable to true or false and alters the text to match
void UTimeTrialMenuWidget::toggleGhostEnabled()
{
	// Swaps the is ghost enabled boolean
	m_pMainGameObject->setIsGhostEnabled( !m_pMainGameObject->getIsGhostEnabled() );

	if( m_pMainGameObject->getIsGhostEnabled() )
	{
		// Changes the text to reflect the setting change
		EnableGhostText->SetText( FText::FromString( FString( k_showGhostText ) ) );
	}
	else
	{
		// Changes the text to reflect the setting change
		EnableGhostText->SetText( FText::FromString( FString( k_hideGhostText ) ) );
	}
}