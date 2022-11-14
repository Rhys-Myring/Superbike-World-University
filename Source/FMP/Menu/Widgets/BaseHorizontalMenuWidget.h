// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "BaseHorizontalMenuWidget.generated.h"

// Forward class declaration
class UDataTable;

/**
 * 
 */
UCLASS()
class FMP_API UBaseHorizontalMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
	
protected:
	const UDataTable* m_pDataTable;		// Pointer to datatable that contains all the menu selections and their corresponding info
	TArray<FName>*	  m_pRowNames;		// Stores the names of all the rows loaded from the datatable

	// Displays the information of the current menu option (Function to be overriden)
	virtual void populateData();

	// Gets the correct data table for the current menu (Function to be overriden)
	virtual const UDataTable* getCorrespondingDataTable() const;

public:
	// Constructor
	UBaseHorizontalMenuWidget( const FObjectInitializer& ObjectInitializer );

	// Destructor
	virtual ~UBaseHorizontalMenuWidget();

	// Override - Loads values from the corresponding data table
	bool Initialize() override;

	// Override - Sets the currently selected option to the previous one and displays new data
	bool previousOption() override;

	// Override - Sets the currently selected option to the next one and displays new data
	bool nextOption() override;
};
