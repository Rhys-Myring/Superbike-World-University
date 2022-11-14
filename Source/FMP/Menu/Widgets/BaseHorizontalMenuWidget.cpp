// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHorizontalMenuWidget.h"
#include "Engine/DataTable.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuTypes.h"
#include "FMP/Menu/MenuTypes.h"

// Constructor
UBaseHorizontalMenuWidget::UBaseHorizontalMenuWidget( const FObjectInitializer& ObjectInitializer )
	:UBaseMenuWidget( ObjectInitializer )
{
	// Sets the menu type to horizontal
	*m_pMenuType = MenuTypes::Horizontal;

	// Sets data table pointer to null by default
	m_pDataTable = nullptr;

	// Initialises row name array
	m_pRowNames = new TArray<FName>();
}

// Destructor
UBaseHorizontalMenuWidget::~UBaseHorizontalMenuWidget()
{
}

// Carries out regular intialisation and loads values from the correct data table
bool UBaseHorizontalMenuWidget::Initialize()
{
	// Calls base class Intialize function
	if( UBaseMenuWidget::Initialize() )
	{
		// Checks if the main game object pointer is null (In case the cast failed or opened in editor)
		if( m_pMainGameObject )
		{
			// Gets the data table
			m_pDataTable = getCorrespondingDataTable();

			// Sets number of indexes to the number of rows in the datatable
			m_numOfIndexes = m_pDataTable->GetRowNames().Num();

			// Stores all the row names
			*m_pRowNames = m_pDataTable->GetRowNames();

			// Displays the information of the initial menu option
			populateData();
		}

		// Returns true if initialisation is successful
		return true;
	}

	// Returns false if initialisation is unsuccessful
	return false;
}

// Sets the currently selected option to the previous oneand displays new data
bool UBaseHorizontalMenuWidget::previousOption()
{
	// Calls base class previous option
	if( UBaseMenuWidget::previousOption() )
	{
		// Displays the information of the newly selected menu option
		populateData();

		// Returns true if the menu option has changed
		return true;
	}

	// Returns false if the menu option hasn't changed
	return false;
}

// Sets the currently selected option to the next one and displays new data
bool UBaseHorizontalMenuWidget::nextOption()
{
	// Calls base class next option
	if( UBaseMenuWidget::nextOption() )
	{
		// Displays the information of the newly selected menu option
		populateData();

		// Returns true if the menu option has changed
		return true;
	}

	// Returns false if the menu option hasn't changed
	return false;
}

// Displays the information of the current menu option (Function to be overriden)
void UBaseHorizontalMenuWidget::populateData()
{
}

// Gets the correct data table for the current menu (Function to be overriden)
const UDataTable* UBaseHorizontalMenuWidget::getCorrespondingDataTable() const
{
	return nullptr;
}


