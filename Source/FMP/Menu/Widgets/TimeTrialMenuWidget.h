// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVerticalMenuWidget.h"
#include "TimeTrialMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FMP_API UTimeTrialMenuWidget : public UBaseVerticalMenuWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadWrite, meta = ( BindWidget ) )
	class UTextBlock* EnableGhostText; // Text that shows whether ghost playback is enabled or not

	// Constructor
	UTimeTrialMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UTimeTrialMenuWidget();

	// Override - Loads new menu based on the selected option
	void selectCurrentOption() override;

	// Override - Returns to the main menu as that is the previous menu before the time trial one
	void back() override;

private:
	// Sets the ghost enabled variable to true or false and alters the text to match
	void toggleGhostEnabled();

};
