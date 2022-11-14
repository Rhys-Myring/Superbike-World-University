// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SafeShutDownGameInstance.generated.h"

// Forward Class Declaration
class AMainGameClass;

/**
 * 
 */
UCLASS()
class FMP_API USafeShutDownGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	AMainGameClass* m_pMainGameObject;

public:
	// Constructor
	USafeShutDownGameInstance();

	// Destructor
	~USafeShutDownGameInstance();

	// Mandatory Override to avoid error
	virtual void Init() override;

	// Mandatory Override to avoid error
	virtual void StartGameInstance() override;

	// Override - Shuts down the game safely
	virtual void Shutdown() override;
	
	// Sets the reference to the main game object
	void setMainGameModeReference( AMainGameClass* mainGameObject );
};
