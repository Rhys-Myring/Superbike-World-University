// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "StartPageWidget.generated.h"

/**
 * 
 */
UCLASS()
class FMP_API UStartPageWidget : public UBaseMenuWidget
{
	GENERATED_BODY()

public:
	// Constructor
	UStartPageWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UStartPageWidget();

	// Override - Changes the menu to the main menu
	void selectCurrentOption() override;

	// Override - Closes game as the Start page is the first page in the menu system
	void back() override;
};
