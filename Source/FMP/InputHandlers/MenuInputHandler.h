// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MenuInputHandler.generated.h"

// Forward Class Declaration
class MenuManager;

UCLASS()
class FMP_API AMenuInputHandler : public APawn
{
	GENERATED_BODY()

private:
	MenuManager* m_pMenuManager; // Stores reference to the menu manager so the menu input manager can interact with it

	// Proceeds the current menu
	void menuProceed();

	// Goes back from the current menu
	void menuBack();

	// Goes up a selection in the menu
	void menuUp();

	// Goes down a selection in the menu
	void menuDown();

	// Goes left a selection in the menu
	void menuLeft();

	// Goes right a selection in the menu
	void menuRight();

public:
	// Constructor
	AMenuInputHandler();

	// Destructor
	~AMenuInputHandler();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
