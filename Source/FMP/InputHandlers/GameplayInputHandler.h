// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameplayInputHandler.generated.h"

// Forward class declaration
class ABike;

UCLASS()
class FMP_API AGameplayInputHandler : public APawn
{
	GENERATED_BODY()

private:
	ABike* m_pBikeToControl;	// Stores a pointer to the bike being controller

	// Sets bike's braking input
	void brake( float brakeAxis );
	
	// Pauses the game
	void pause();

	// Sets bike's steering input
	void steer( float steerAxis );
	
	// Sets bike's throttle input
	void throttle( float throttleAxis );

public:
	// Constructor
	AGameplayInputHandler();
	
	// Destructor
	~AGameplayInputHandler();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( class UInputComponent* inputComponent ) override;

	// Sets which bike is being controlled
	void setBikeToControl( ABike* bikeToControl );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
