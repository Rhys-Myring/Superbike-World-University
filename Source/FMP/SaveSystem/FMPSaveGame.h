// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FMPSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FMP_API UFMPSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    // Float to store all the best lap time for the track
    UPROPERTY( VisibleAnywhere, Category = Basic )
    float m_time;

    // Array to store all the x positions of the ghost
    UPROPERTY( VisibleAnywhere, Category = Basic )
    TArray<float> m_xPositions;

    // Array to store all the y positions of the ghost
    UPROPERTY( VisibleAnywhere, Category = Basic )
    TArray<float> m_yPositions;

    // Array to store all the z positions of the ghost
    UPROPERTY( VisibleAnywhere, Category = Basic )
    TArray<float> m_zPositions;

    // Array to store all the x rotations of the ghost
    UPROPERTY( VisibleAnywhere, Category = Basic )
    TArray<float> m_xRotations;

    // Array to store all the y rotations of the ghost
    UPROPERTY( VisibleAnywhere, Category = Basic )
    TArray<float> m_yRotations;

    // Array to store all the z rotations of the ghost
    UPROPERTY( VisibleAnywhere, Category = Basic )
    TArray<float> m_zRotations;

    // Constructor
    UFMPSaveGame();

    // Destructor
    ~UFMPSaveGame();
};
