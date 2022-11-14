// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenuWidget.h"
#include "Components/TextBlock.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "FMP/DataTables/TrackDataTableStruct.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"
#include "FMP/Misc/Constants.h"
#include "Kismet/GameplayStatics.h"


// Constructor
UOptionsMenuWidget::UOptionsMenuWidget( const FObjectInitializer& ObjectInitializer ) :UBaseVerticalMenuWidget( ObjectInitializer )
{
	// Sets muted text to null by default
	MuteSoundsText = nullptr;
}

// Destructor
UOptionsMenuWidget::~UOptionsMenuWidget()
{
}

// Loads new menu based on the selected option
void UOptionsMenuWidget::selectCurrentOption()
{
	switch( m_currentlySelectedIndex )
	{
		// If the mute sounds button is clicked
		case 0:
			
			// Mutes or unmutes the game sound and changes the text accordingly
			toggleMuteEnabled();

			break;

		// If the delete data button is clicked
		case 1:
			
			// Deletes all of the save files
			deleteAllSaveData();
			
			break;

		// If the return to menu button is clicked
		case 2:

			// Sets menu to the main menu
			m_pMenuManager->setMenuScreen( MenuScreen::MainMenu );

			break;

		default:
			break;
	}
}

// Returns to the main menu as that is the previous menu before the options menu
void UOptionsMenuWidget::back()
{
	// Sets menu to the main menu
	m_pMenuManager->setMenuScreen( MenuScreen::MainMenu );
}

// Deletes all of the save files
void UOptionsMenuWidget::deleteAllSaveData()
{
	// Gets all the track names
	TArray<FName> trackNames = m_pMainGameObject->getTracksDT()->GetRowNames();
	
	// Iterates through all the tracks
	for( int i = 0; i < trackNames.Num(); i++ )
	{
		// Deletes data			
		UGameplayStatics::DeleteGameInSlot( trackNames[i].ToString(), k_slotIndex);
	}
}

// Sets the mute enabled variable to true or false and alters the text to match
void UOptionsMenuWidget::toggleMuteEnabled()
{
	// Swaps the is mute enabled boolean
	m_pMainGameObject->setIsSoundMuted( !m_pMainGameObject->getIsSoundMuted() );

	if( m_pMainGameObject->getIsSoundMuted() )
	{
		// Changes the text to reflect the setting change
		MuteSoundsText->SetText( FText::FromString( FString( k_playSoundText ) ) );
	}
	else
	{
		// Changes the text to reflect the setting change
		MuteSoundsText->SetText( FText::FromString( FString( k_muteSoundText ) ) );
	}
}