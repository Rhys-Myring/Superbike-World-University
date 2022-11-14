// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVerticalMenuWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FMP_API UPauseMenuWidget : public UBaseVerticalMenuWidget
{
	GENERATED_BODY()
	
public:
	// Constructor
	UPauseMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UPauseMenuWidget();

	// Override - Sets the paused state or returns the player to the menu based on what option is selected 
	void selectCurrentOption() override;

	// Override - Unpauses the game
	void back() override;
};
