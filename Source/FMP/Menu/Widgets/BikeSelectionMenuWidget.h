// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHorizontalMenuWidget.h"
#include "BikeSelectionMenuWidget.generated.h"

// Forward Struct declaration
struct FBikeDataTableStruct;

/**
 *
 */
UCLASS()
class FMP_API UBikeSelectionMenuWidget : public UBaseHorizontalMenuWidget
{
	GENERATED_BODY()

private:
	FBikeDataTableStruct*	m_pCurrentRow;	// Stores the current row of the bikes datatable

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UImage* BikeImage; // Image that shows the current bike

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* BikeNameText; // Text that shows the name of the current bike

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* BikeNumberText; // Text that shows the how many bikes there are to choose from

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* CapacityText; // Text that shows the size of the bike's engine

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* ManufacturerText; // Text that shows the name of the manufacturer of the current bike

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* PowerText; // Text that shows the maximum power the bike has

	UPROPERTY( EditAnywhere, meta = ( BindWidget ) )
	class UTextBlock* TorqueText; // Text that shows the maximum torque the bike has


public:
	// Constructor
	UBikeSelectionMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UBikeSelectionMenuWidget();

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
