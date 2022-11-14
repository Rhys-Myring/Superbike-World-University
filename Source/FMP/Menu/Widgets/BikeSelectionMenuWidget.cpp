// Fill out your copyright notice in the Description page of Project Settings.


#include "BikeSelectionMenuWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FMP/DataTables/BikeDataTableStruct.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"

// Constructor
UBikeSelectionMenuWidget::UBikeSelectionMenuWidget( const FObjectInitializer& ObjectInitializer )
	:UBaseHorizontalMenuWidget( ObjectInitializer )
{
	// Sets the uproperties to null by default
	BikeImage = nullptr;
	BikeNameText = nullptr;
	BikeNumberText = nullptr;
	CapacityText = nullptr;
	ManufacturerText = nullptr;
	PowerText = nullptr;
	TorqueText = nullptr;
	
	// Sets current row pointer to null
	m_pCurrentRow = nullptr;
}

// Destructor
UBikeSelectionMenuWidget::~UBikeSelectionMenuWidget()
{
}

// Displays the information of the currently selected bike
void UBikeSelectionMenuWidget::populateData()
{
	// Checks if the datatable pointer is null
	if( m_pDataTable )
	{
		// Gets the row of the currently selected bike
		m_pCurrentRow = m_pDataTable->FindRow<FBikeDataTableStruct>( ( *m_pRowNames )[m_currentlySelectedIndex], "" );

		// Sets Bike Image
		BikeImage->SetBrushFromTexture( m_pCurrentRow->BikeImage.LoadSynchronous() );

		// Sets Bike Name Text
		BikeNameText->SetText( FText::FromString( m_pCurrentRow->UIName ) );

		// Sets bike manufacturer Name Text
		ManufacturerText->SetText( FText::FromString( FString( "Manufacturer: " ) + m_pCurrentRow->Manufacturer ) );

		// Sets bike's power Text
		PowerText->SetText( FText::FromString( FString( "Maximum Power: " ) + FString::FromInt( m_pCurrentRow->Power ) 
			+ FString( "HP" ) ) );

		// Sets bike's torque Text
		TorqueText->SetText( FText::FromString( FString( "Maximum Torque: " ) + FString::FromInt( m_pCurrentRow->Torque )
			+ FString( "N/m" ) ) );

		// Sets bike's engine size Text
		CapacityText->SetText( FText::FromString( FString( "Displacement: " ) + FString::FromInt( m_pCurrentRow->Capacity ) 
			+ FString( "cc" ) ) );

		// Sets Bike Number Text
		BikeNumberText->SetText( FText::FromString( FString( "< " ) + FString::FromInt( m_currentlySelectedIndex + 1 ) +
			FString( "/" ) + FString::FromInt( m_pRowNames->Num() ) + FString( " >" ) ) );
	}
}

// Gets the bikes data table
const UDataTable* UBikeSelectionMenuWidget::getCorrespondingDataTable() const
{
	return m_pMainGameObject->getBikesDT();
}

// Sets bike variable based on the selected option
void UBikeSelectionMenuWidget::selectCurrentOption()
{
	// Sets the currently selected Bike
	m_pMainGameObject->setSelectedBike(
		( *m_pRowNames )[m_currentlySelectedIndex].ToString() );

	// Sets menu to the time trial menu
	m_pMenuManager->setMenuScreen( MenuScreen::TimeTrial );
}

// Returns to the time trial menu as that is the previous menu before the bike selection
void UBikeSelectionMenuWidget::back()
{
	// Sets menu to the time trial menu
	m_pMenuManager->setMenuScreen( MenuScreen::TimeTrial );
}