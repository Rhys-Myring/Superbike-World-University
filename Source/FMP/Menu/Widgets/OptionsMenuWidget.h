// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVerticalMenuWidget.h"
#include "OptionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FMP_API UOptionsMenuWidget : public UBaseVerticalMenuWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadWrite, meta = ( BindWidget ) )
	class UTextBlock* MuteSoundsText; // Text that shows whether the sound is enabled or not

	// Constructor
	UOptionsMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UOptionsMenuWidget();

	// Override - Changes specific value within the game, depending on what is selected
	void selectCurrentOption() override;

	// Override - Closes game as the main menu is the first proper menu
	void back() override;

private:
	// Deletes all of the save files
	void deleteAllSaveData();
	
	// Sets the mute enabled variable to true or false and alters the text to match
	void toggleMuteEnabled();
};
