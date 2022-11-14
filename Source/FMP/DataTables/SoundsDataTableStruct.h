// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SoundsDataTableStruct.generated.h"

// Forward Class Declaration
class USoundBase;

/**
 * 
 */
USTRUCT( BlueprintType )
struct FMP_API FSoundsDataTableStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
    // Constructor
    FSoundsDataTableStruct()
        : Sound( nullptr )
    {
    }

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Sounds )
    USoundBase* Sound; // Stores a reference to the sound cue of the menu sound
};
