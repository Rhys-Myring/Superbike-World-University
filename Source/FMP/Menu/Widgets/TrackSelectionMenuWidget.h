// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHorizontalMenuWidget.h"
#include "TrackSelectionMenuWidget.generated.h"

// Forward struct declaration
struct FTrackDataTableStruct;

// Forward class declaration
class UDataTable;

/**
 * 
 */
UCLASS()
class FMP_API UTrackSelectionMenuWidget : public UBaseHorizontalMenuWidget
{
	GENERATED_BODY()

private:
	FTrackDataTableStruct*	m_pCurrentRow;	// Stores the current row of the tracks datatable

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* CountryText; // Text that shows the country of the current track

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* ConstructedText; // Text that shows the construction date of the current track

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* LengthText; // Text that shows the length the current track

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UImage* TrackMapImage; // Image that shows the map of the current track

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* TrackNameText; // Text that shows the name of the current track

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* TrackNumberText; // Text that shows the how many tracks there is to choose from

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* TurnsText; // Text that shows the number of turns on the current track

public:
	// Constructor
	UTrackSelectionMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UTrackSelectionMenuWidget();

	// Override - Sets track variable based on the selected option
	void selectCurrentOption() override;

	// Override - Returns to the time trial menu as that is the previous menu before the track selection
	void back() override;

protected:
	// Override - Displays the information of the currently selected track
	void populateData() override;

	// Override - Gets the bikes data table
	const UDataTable* getCorrespondingDataTable() const override;
};
