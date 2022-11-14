// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TrackDataTableStruct.generated.h"

/**
 * 
 */
USTRUCT( BlueprintType )
struct FMP_API FTrackDataTableStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
    // Constructor
    FTrackDataTableStruct()
        : Turns( 0 )
        , Length( 0 )
        , Constructed( 0 )
    {
    }

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Tracks )
    FString UIName; // Stores the visual name of the track

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Tracks )
    FString Country; // Stores the country name of the track

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Tracks )
    int Turns; // Stores the number of turns on the track

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Tracks )
    int Length; // Stores the length the track

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Tracks )
    int Constructed; // Stores the year the track was built

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Tracks )
    TSoftObjectPtr<UTexture2D> MapImage; // Stores a reference to the track map image
	
};
