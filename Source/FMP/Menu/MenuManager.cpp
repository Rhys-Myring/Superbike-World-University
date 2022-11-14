// Don't put includes on this line as it breaks intellisense

#include "MenuManager.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "FMP/DataTables/WidgetDataTableStruct.h"
#include "FMP/DataTables/SoundsDataTableStruct.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuScreens.h"
#include "FMP/Menu/MenuTypes.h"
#include "FMP/Menu/Widgets/BaseMenuWidget.h"
#include "FMP/Menu/Widgets/BikeSelectionMenuWidget.h"
#include "FMP/Menu/Widgets/MainMenuWidget.h"
#include "FMP/Menu/Widgets/OptionsMenuWidget.h"
#include "FMP/Menu/Widgets/PauseMenuWidget.h"
#include "FMP/Menu/Widgets/StartPageWidget.h"
#include "FMP/Menu/Widgets/TimeTrialMenuWidget.h"
#include "FMP/Menu/Widgets/TrackSelectionMenuWidget.h"
#include "FMP/Misc/Constants.h"
#include "FMP/Misc/Helpers.h"
#include "Kismet/GameplayStatics.h"

// Constructor
MenuManager::MenuManager( AMainGameClass* mainGameObject )
{
	// Stores reference to main game mode
	m_pMainGameObject = mainGameObject;

	// Sets menu widget pointers to null initially as they have to be created when play begins
	m_pBikeSelectionWidget = nullptr;
	m_pCurrentMenuWidget = nullptr;
	m_pMainMenu = nullptr;
	m_pOptionsMenuWidget = nullptr;
	m_pPauseMenuWidget = nullptr;
	m_pStartPage = nullptr;
	m_pTimeTrialWidget = nullptr;
	m_pTrackSelectionWidget = nullptr;
}

// Destructor
MenuManager::~MenuManager()
{
}

// Creates all the widgets for the menus
void MenuManager::createAllWidgets()
{
	// Creates bike selection menu widget
	m_pBikeSelectionWidget = CreateWidget<UBikeSelectionMenuWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_bikeSelectionMenu, "" )->Widget.LoadSynchronous() );

	// Creates main menu widget
	m_pMainMenu = CreateWidget<UMainMenuWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_mainMenu, "" )->Widget.LoadSynchronous() );

	// Creates options menu widget
	m_pOptionsMenuWidget = CreateWidget<UOptionsMenuWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_optionsMenu, "" )->Widget.LoadSynchronous() );

	// Creates pause menu widget
	m_pPauseMenuWidget = CreateWidget<UPauseMenuWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_pauseMenu, "" )->Widget.LoadSynchronous() );

	// Creates start page widget
	m_pStartPage = CreateWidget<UStartPageWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_startPage, "" )->Widget.LoadSynchronous() );

	// Creates time trial menu widget
	m_pTimeTrialWidget = CreateWidget<UTimeTrialMenuWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_timeTrialMenu, "" )->Widget.LoadSynchronous() );

	// Creates track selection menu widget
	m_pTrackSelectionWidget = CreateWidget<UTrackSelectionMenuWidget>( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getWidgetsDT()->FindRow<FWidgetDataTableStruct>( k_trackSelectionMenu, "" )->Widget.LoadSynchronous() );
}

// Sets up all the widgets for the menus
void MenuManager::setUpWidgets()
{
	// Creates all the widgets for the menus
	createAllWidgets();

	// Sets current menu widget to the start page
	m_pCurrentMenuWidget = m_pStartPage;

	// Adds start page widget to the screen
	m_pCurrentMenuWidget->AddToViewport();
}

// Proceeds the current menu
void MenuManager::menuProceed()
{
	// Plays Menu Proceed Sound
	UGameplayStatics::PlaySound2D( m_pMainGameObject->GetWorld(), 
		m_pMainGameObject->getSoundsDT()->FindRow<FSoundsDataTableStruct>( k_proceedSound, "" )->Sound,
		m_pMainGameObject->getGlobalVolume() );

	// Selects the current option from the menu
	m_pCurrentMenuWidget->selectCurrentOption();
}

// Goes back from the current menu
void MenuManager::menuBack()
{
	// Plays Menu Back Sound
	UGameplayStatics::PlaySound2D( m_pMainGameObject->GetWorld(),
		m_pMainGameObject->getSoundsDT()->FindRow<FSoundsDataTableStruct>( k_backSound, "" )->Sound,
		m_pMainGameObject->getGlobalVolume() );

	// Goes back from the current menu to the previous one
	m_pCurrentMenuWidget->back();
}

// Goes up in the current menu
void MenuManager::menuUp()
{
	// If current menu is vertical
	if( *( m_pCurrentMenuWidget->getType() ) == MenuTypes::Vertical )
	{
		// Goes up one option
		if( m_pCurrentMenuWidget->previousOption() )
		{
			// Plays Menu Scroll Vertical Sound if the menu option has changed
			UGameplayStatics::PlaySound2D( m_pMainGameObject->GetWorld(),
				m_pMainGameObject->getSoundsDT()->FindRow<FSoundsDataTableStruct>( k_scrollVerticalSound, "" )->Sound,
				m_pMainGameObject->getGlobalVolume() );
		}
	}
}

// Goes down in the current menu
void MenuManager::menuDown()
{
	// If current menu is vertical
	if( *( m_pCurrentMenuWidget->getType() ) == MenuTypes::Vertical )
	{
		// Goes down one option
		if( m_pCurrentMenuWidget->nextOption() )
		{
			// Plays Menu Scroll Vertical Sound if the menu option has changed
			UGameplayStatics::PlaySound2D( m_pMainGameObject->GetWorld(),
				m_pMainGameObject->getSoundsDT()->FindRow<FSoundsDataTableStruct>( k_scrollVerticalSound, "" )->Sound,
				m_pMainGameObject->getGlobalVolume() );
		}
	}
}

// Goes left in the current menu
void MenuManager::menuLeft()
{
	// If current menu is horizontal
	if( *( m_pCurrentMenuWidget->getType() ) == MenuTypes::Horizontal )
	{
		// Goes left one option
		if( m_pCurrentMenuWidget->previousOption() )
		{
			// Plays Menu Scroll Horizontal Sound if the menu option has changed
			UGameplayStatics::PlaySound2D( m_pMainGameObject->GetWorld(),
				m_pMainGameObject->getSoundsDT()->FindRow<FSoundsDataTableStruct>( k_scrollHorizontalSound, "" )->Sound,
				m_pMainGameObject->getGlobalVolume() );
		}
	}
}

// Goes right in the current menu
void MenuManager::menuRight()
{
	// If current menu is horizontal
	if( *( m_pCurrentMenuWidget->getType() ) == MenuTypes::Horizontal )
	{
		// Goes right one option
		if( m_pCurrentMenuWidget->nextOption() )
		{
			// Plays Menu Scroll Horizontal Sound if the menu option has changed
			UGameplayStatics::PlaySound2D( m_pMainGameObject->GetWorld(),
				m_pMainGameObject->getSoundsDT()->FindRow<FSoundsDataTableStruct>( k_scrollHorizontalSound, "" )->Sound,
				m_pMainGameObject->getGlobalVolume() );
		}
	}
}

// Sets the current menu screen
void MenuManager::setMenuScreen( MenuScreen newMenu )
{
	// Checks whether the current menu is in the view port
	if( m_pCurrentMenuWidget->IsInViewport() )
	{
		// Removes menu from viewport if it was in the viewport
		m_pCurrentMenuWidget->RemoveFromViewport();
	}

	// Sets current menu variable based on the screen passed in
	switch( newMenu )
	{
		// If the new menu is the main menu
		case MenuScreen::MainMenu:			
			// Sets current menu to the main menu
			m_pCurrentMenuWidget = m_pMainMenu;
			break;

		// If the new menu is the options menu
		case MenuScreen::Options:
			// Sets current menu to the options menu
			m_pCurrentMenuWidget = m_pOptionsMenuWidget;
			break;

		// If the new menu is the pause menu
		case MenuScreen::Pause:
			// Sets current menu to the pause menu
			m_pCurrentMenuWidget = m_pPauseMenuWidget;
			break;

		// If the new menu is the select bike menu
		case MenuScreen::SelectBike:
			// Sets current menu to the bike selection menu
			m_pCurrentMenuWidget = m_pBikeSelectionWidget;
			break;

		// If the new menu is the select track menu
		case MenuScreen::SelectTrack:
			// Sets current menu to the track selection menu
			m_pCurrentMenuWidget = m_pTrackSelectionWidget;
			break;
			
		// If the new menu is the time trial menu
		case MenuScreen::TimeTrial:
			// Sets current menu to the time trial menu
			m_pCurrentMenuWidget = m_pTimeTrialWidget;
			break;

		// If the new menu is the start page
		case MenuScreen::StartPage:			
			// Sets current menu to the start page
			m_pCurrentMenuWidget = m_pStartPage;
			break;

		// If the new menu isn't a valid menu nothing happens
		default:
			break;
	}

	// Adds new menu to the screen
	m_pCurrentMenuWidget->AddToViewport();
}

// Hides the current menu
void MenuManager::hideMenu()
{
	m_pCurrentMenuWidget->RemoveFromViewport();
}

// Updates the current menu
void MenuManager::update()
{
	m_pCurrentMenuWidget->update();
}

// Unroots all widgets before exiting the game to avoid a crash
void MenuManager::unrootAllWidgets()
{
	m_pBikeSelectionWidget->RemoveFromRoot();
	m_pMainMenu->RemoveFromRoot();
	m_pOptionsMenuWidget->RemoveFromRoot();
	m_pPauseMenuWidget->RemoveFromRoot();
	m_pStartPage->RemoveFromRoot();
	m_pTimeTrialWidget->RemoveFromRoot();
	m_pTrackSelectionWidget->RemoveFromRoot();
}
