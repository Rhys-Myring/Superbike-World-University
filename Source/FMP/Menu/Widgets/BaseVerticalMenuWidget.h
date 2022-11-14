// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "BaseVerticalMenuWidget.generated.h"

// Forward class declaration
class UGridSlot;

/**
 * 
 */
UCLASS()
class FMP_API UBaseVerticalMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
	
private:
	UGridSlot* m_pSelectedBackgroundSlot; // Stores the grid slot of the selected background

public:
	UPROPERTY( BlueprintReadWrite, meta = ( BindWidget ) )
	class UGridPanel* MenuOptions; // Panel that holds all the text and selection backdrop

	UPROPERTY( BlueprintReadWrite, meta = ( BindWidget ) )
	class UImage* SelectedBackground; // Background that highlights the current selection

	// Constructor
	UBaseVerticalMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UBaseVerticalMenuWidget();

	// Override - Carries out regular intialisation and then sets some values that can only be set after the game has started
	bool Initialize() override;

	// Override - Sets the currently selected option to the previous one and moves the selection background
	bool previousOption() override;

	// Override - Sets the currently selected option to the next one and moves the selection background
	bool nextOption() override;
};
