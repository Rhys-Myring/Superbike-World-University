// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPageWidget.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "FMP/Menu/MenuManager.h"
#include "FMP/Menu/MenuScreens.h"
#include "Kismet/GameplayStatics.h"

// Constructor
UStartPageWidget::UStartPageWidget( const FObjectInitializer& ObjectInitializer ) :UBaseMenuWidget( ObjectInitializer )
{
	// Sets number of menu options to 1
	m_numOfIndexes = 1;
}

// Destructor
UStartPageWidget::~UStartPageWidget()
{
}

// Changes the menu to the main menu
void UStartPageWidget::selectCurrentOption()
{
	// Sets menu to the main menu
	m_pMenuManager->setMenuScreen( MenuScreen::MainMenu );
}

// Closes game as the Start page is the first page in the menu system
void UStartPageWidget::back()
{
	// Exits game
	FGenericPlatformMisc::RequestExit( false );
}