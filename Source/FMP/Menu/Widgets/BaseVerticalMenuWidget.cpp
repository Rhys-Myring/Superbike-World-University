// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVerticalMenuWidget.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"

// Constructor
UBaseVerticalMenuWidget::UBaseVerticalMenuWidget( const FObjectInitializer& ObjectInitializer ) :UBaseMenuWidget( ObjectInitializer )
{
	// Sets all uproperties to null by default
	m_pSelectedBackgroundSlot = nullptr;
	MenuOptions = nullptr;
	SelectedBackground = nullptr;
}

// Destructor
UBaseVerticalMenuWidget::~UBaseVerticalMenuWidget()
{
}

// Carries out regular intialisation and then sets some values that can only be set after the game has started
bool UBaseVerticalMenuWidget::Initialize()
{
	// Carries out base intialisation
	if( UBaseMenuWidget::Initialize() )
	{
		// Stores grid slot of the selection backdrop:
		// If both the menu options panel and the selected background exist
		if( MenuOptions && SelectedBackground )
		{
			// Sets the number of indexes based on the number of items in the grid panel (-1 as there is the selection background) 
			m_numOfIndexes = MenuOptions->GetAllChildren().Num() - 1;

			// Stores the grid slot of the selected background
			m_pSelectedBackgroundSlot = Cast<UGridSlot>( SelectedBackground->Slot );
		}

		// Returns true if intialisation is successful
		return true;
	}

	// Returns false if intialisation is unsuccessful
	return false;
}

// Sets the currently selected option to the previous one and moves the selection background
bool UBaseVerticalMenuWidget::previousOption()
{
	// Calls base class previous option
	if( UBaseMenuWidget::previousOption() )
	{
		// Sets the highlighted background position to the currently selected menu option
		m_pSelectedBackgroundSlot->SetRow(m_currentlySelectedIndex);

		// Returns true if the menu option has changed
		return true;
	}

	// Returns false if the menu option hasn't changed
	return false;
}

// Sets the currently selected option to the next one and moves the selection background
bool UBaseVerticalMenuWidget::nextOption()
{
	// Calls base class next option
	if (UBaseMenuWidget::nextOption())
	{
		// Sets the highlighted background position to the currently selected menu option
		m_pSelectedBackgroundSlot->SetRow(m_currentlySelectedIndex);

		// Returns true if the menu option has changed
		return true;
	}

	// Returns false if the menu option hasn't changed
	return false;
}