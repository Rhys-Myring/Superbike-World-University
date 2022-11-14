// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMenuWidget.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuTypes.h"
#include "FMP/Misc/Helpers.h"

// Constructor
UBaseMenuWidget::UBaseMenuWidget( const FObjectInitializer& ObjectInitializer ) :UUserWidget( ObjectInitializer )
{
	// Sets initial values for the number of indexes
	m_currentlySelectedIndex = 0;
	m_numOfIndexes = 0;
	
	// Initialises menu type
	m_pMenuType = new MenuTypes();
	*m_pMenuType = MenuTypes::Vertical;

	// Sets main game object reference to null intially as it must be set later
	m_pMainGameObject = nullptr;

	// Sets menu manager reference to null intially as it must be set later
	m_pMenuManager = nullptr;
}

// Destructor
UBaseMenuWidget::~UBaseMenuWidget()
{
	// Deletes pointer to avoid memory leak
	safeDelete( m_pMenuType );
}

// Getter
MenuTypes* UBaseMenuWidget::getType()
{
	return m_pMenuType;
}

/* Carries out regular intialisation, stops the widget being deleted 
   and sets some references that can only be set after the game has started */
bool UBaseMenuWidget::Initialize()
{
	// Carries out base intialisation
	if( UUserWidget::Initialize() )
	{
		// Gets the main game mode and stores a reference to it
		m_pMainGameObject = static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() );

		// If the main game object isn't null (In case the cast failed or opened in editor)
		if( m_pMainGameObject )
		{
			// Gets the menu manager from the base game mode and stores a reference to it
			m_pMenuManager = m_pMainGameObject->getMenuManager();

			// Stops this widget being deleted by the garbage collector
			AddToRoot();
		}

		// Returns true if intialisation is successful
		return true;
	}

	// Returns false if intialisation is unsuccessful
	return false;
}

// Selects the current option ( Function to be overriden )
void UBaseMenuWidget::selectCurrentOption()
{
}

// Goes back to the previous menu ( Function to be overriden )
void UBaseMenuWidget::back()
{
}

// Sets the currently selected option to the previous one
bool UBaseMenuWidget::previousOption()
{
	// Decreases the index that is currently selected as long as the it is more than the first index 
	if( m_currentlySelectedIndex > 0 )
	{
		m_currentlySelectedIndex--;

		return true;
	}

	// Returns false if the selected menu option is currently the first one
	return false;
}

// Sets the currently selected option to the next one
bool UBaseMenuWidget::nextOption()
{
	// Increases the index that is currently selected as long as the it is less than the last index 
	if( m_currentlySelectedIndex < m_numOfIndexes - 1 )
	{
		m_currentlySelectedIndex++;

		return true;
	}

	// Returns false if the selected menu option is currently the last one
	return false;
}

// Updates the object ( Function to be overriden )
void UBaseMenuWidget::update()
{
}
