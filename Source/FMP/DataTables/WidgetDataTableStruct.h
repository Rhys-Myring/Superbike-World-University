// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WidgetDataTableStruct.generated.h"

// Forward Class Declaration
class UUserWidget;

/**
 * 
 */
USTRUCT( BlueprintType )
struct FMP_API FWidgetDataTableStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
    // Constructor
    FWidgetDataTableStruct()
        : Widget( nullptr )
    {
    }

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Widgets )
    TSoftClassPtr <UUserWidget> Widget; // Stores a reference to the widget for this row
	
};
