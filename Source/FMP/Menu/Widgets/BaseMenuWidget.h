// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseMenuWidget.generated.h"

// Forward class declarations
enum class MenuTypes;
class AMainGameClass;
class MenuManager;

/**
 * 
 */
UCLASS()
class FMP_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	int					m_currentlySelectedIndex;	// Stores the index currently selected menu option
	AMainGameClass*		m_pMainGameObject;			// Stores reference to the main game mode so that its values can be changed
	MenuManager*		m_pMenuManager;				// Stores reference to the menu manager so the screen can be changed
	MenuTypes*			m_pMenuType;				// Stores the type of menu
	int					m_numOfIndexes;				// Stores the number of menu options

public:
	// Constructor
	UBaseMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UBaseMenuWidget();

	// Returns what type of menu this menu is
	MenuTypes* getType();

	/* Override - Carries out regular intialisation, stops the widget being deleted 
	and sets some references that can only be set after the game has started */
	bool Initialize() override;

	// Selects the current option ( Function to be overriden )
	virtual void selectCurrentOption();

	// Returns to the previous menu ( Function to be overriden )
	virtual void back();

	// Sets the currently selected option to the previous one ( Function can be overriden )
	virtual bool previousOption();

	// Sets the currently selected option to the next one ( Function can be overriden )
	virtual bool nextOption();

	// Updates the object ( Function to be overriden )
	virtual void update();
};
