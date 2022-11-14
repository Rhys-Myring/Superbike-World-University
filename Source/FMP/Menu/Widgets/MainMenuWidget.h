// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVerticalMenuWidget.h"
#include "MainMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class FMP_API UMainMenuWidget : public UBaseVerticalMenuWidget
{
	GENERATED_BODY()

public:
	// Constructor
	UMainMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UMainMenuWidget();

	// Override - Loads new menu based on the selected option
	void selectCurrentOption() override;

	// Override - Closes game as the main menu is the first proper menu
	void back() override;
};
