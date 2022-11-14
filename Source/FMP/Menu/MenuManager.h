// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward Class declarations
enum class MenuScreen;
class AMainGameClass;
class UBaseMenuWidget;
class UBikeSelectionMenuWidget;
class UMainMenuWidget;
class UOptionsMenuWidget;
class UPauseMenuWidget;
class UStartPageWidget;
class UTimeTrialMenuWidget;
class UTrackSelectionMenuWidget;

/**
 *
 */
class FMP_API MenuManager
{
private:
	UBikeSelectionMenuWidget*		m_pBikeSelectionWidget;		// Stores the bike selection menu
	UBaseMenuWidget*				m_pCurrentMenuWidget;		// Stores the current Menu widget
	AMainGameClass*					m_pMainGameObject;			// Stores a reference to main game object so it can be accessed later
	UMainMenuWidget*				m_pMainMenu;				// Stores the main menu
	UOptionsMenuWidget*				m_pOptionsMenuWidget;		// Stores the options menu
	UPauseMenuWidget*				m_pPauseMenuWidget;			// Stores the pause menu
	UStartPageWidget*				m_pStartPage;				// Stores the start page menu
	UTimeTrialMenuWidget*			m_pTimeTrialWidget;			// Stores the time trial menu
	UTrackSelectionMenuWidget*		m_pTrackSelectionWidget;	// Stores the track selection menu

	// Creates all the widgets for the menus
	void createAllWidgets();

public:
	// Constructor
	MenuManager( AMainGameClass* mainGameObject );

	// Destructor
	~MenuManager();

	// Sets up all the widgets for the menus
	void setUpWidgets();

	// Proceeds the current menu
	void menuProceed();

	// Goes back from the current menu
	void menuBack();

	// Goes up in the current menu
	void menuUp();

	// Goes down in the current menu
	void menuDown();

	// Goes left in the current menu
	void menuLeft();

	// Goes right in the current menu
	void menuRight();

	// Sets the current menu screen
	void setMenuScreen( MenuScreen newMenu );

	// Hides the current menu
	void hideMenu();

	// Updates the current menu
	void update();

	// Unroots all widgets before exiting the game to avoid a crash
	void unrootAllWidgets();
};
