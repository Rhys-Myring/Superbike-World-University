// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackSelectionMenuWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FMP/DataTables/TrackDataTableStruct.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"

// Constructor
UTrackSelectionMenuWidget::UTrackSelectionMenuWidget( const FObjectInitializer& ObjectInitializer ) 
	:UBaseHorizontalMenuWidget( ObjectInitializer )
{
	// Sets the uproperties to null by default
	ConstructedText = nullptr;
	CountryText = nullptr;
	LengthText = nullptr;
	TrackMapImage = nullptr;
	TrackNameText = nullptr;
	TrackNumberText = nullptr;
	TurnsText = nullptr;

	// Sets current row pointer to null
	m_pCurrentRow = nullptr;
}

// Destructor
UTrackSelectionMenuWidget::~UTrackSelectionMenuWidget()
{
}

// Displays the information of the currently selected track
void UTrackSelectionMenuWidget::populateData()
{
	// Checks if the datatable pointer is null
	if( m_pDataTable )
	{
		// Gets the row of the currently selected track
		m_pCurrentRow = 
			m_pDataTable->FindRow<FTrackDataTableStruct>( ( *m_pRowNames )[m_currentlySelectedIndex], "" );

		// Sets Track Map Image
		TrackMapImage->SetBrushFromTexture( m_pCurrentRow->MapImage.LoadSynchronous() );

		// Sets Track Name Text
		TrackNameText->SetText( FText::FromString( m_pCurrentRow->UIName ) );

		// Sets Country Name Text
		CountryText->SetText( FText::FromString( FString( "Country: " ) + m_pCurrentRow->Country ) );

		// Sets Turn Number Text
		TurnsText->SetText( FText::FromString( FString( "Turns: " ) + FString::FromInt( m_pCurrentRow->Turns ) ) );
		
		// Sets Length Text
		LengthText->SetText( FText::FromString( FString( "Length: " ) + FString::FromInt( m_pCurrentRow->Length ) + FString( "m" ) ) );
		
		// Sets Constructed Text
		ConstructedText->SetText( FText::FromString( FString( "Built: " ) + FString::FromInt( m_pCurrentRow->Constructed ) ) );

		// Sets Track Number Text
		TrackNumberText->SetText( FText::FromString( FString( "< " ) + FString::FromInt( m_currentlySelectedIndex + 1 ) + 
			FString( "/" ) + FString::FromInt( m_pRowNames->Num() ) + FString( " >" ) ) );
	}
}

// Gets the tracks data table
const UDataTable* UTrackSelectionMenuWidget::getCorrespondingDataTable() const
{
	return m_pMainGameObject->getTracksDT();
}

// Sets track variable based on the selected option
void UTrackSelectionMenuWidget::selectCurrentOption()
{
	// Sets the currently selected Track
	m_pMainGameObject->setSelectedTrack( 
		( *m_pRowNames )[m_currentlySelectedIndex].ToString() );

	// Sets menu to the time trial menu
	m_pMenuManager->setMenuScreen( MenuScreen::TimeTrial );
}

// Returns to the time trial menu as that is the previous menu before the track selection
void UTrackSelectionMenuWidget::back()
{
	// Sets menu to the time trial menu
	m_pMenuManager->setMenuScreen( MenuScreen::TimeTrial );
}