// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FMP_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* BestLapTimeText; // Text that shows the best lap time
	
	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* LapTimeText; // Text that shows the current lap time

public:
	// Constructor
	UHUDWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UHUDWidget();

	// Setters
	void setBestTimeText( FText* bestTimeText );
	void setLapTimeText( FText* lapTimeText );
};
