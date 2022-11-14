// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BikeDataTableStruct.generated.h"

// Forward class declaration
class ABike;

/**
 * 
 */
USTRUCT( BlueprintType )
struct FMP_API FBikeDataTableStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
    // Constructor
    FBikeDataTableStruct()
        : Power( 0 )
        , Torque( 0 )
        , Capacity( 0 )
    {
    }

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    FString UIName; // Stores the visual name of the bike

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    FString Manufacturer; // Stores the manufacturer name of the bike

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    int Power; // Stores the maximum power the bike has

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    int Torque; // Stores the maximum torque the bike has

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    int Capacity; // Stores the size of the bike's engine

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    TSoftObjectPtr<UTexture2D> BikeImage; // Stores a reference to an image of the bike

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    TSoftClassPtr<ABike> BikeClass; // Stores a reference to the class of the bike
	
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Bikes )
    TSoftClassPtr<AActor> BikeGhostClass; // Stores a reference to the ghost class of the bike
};
