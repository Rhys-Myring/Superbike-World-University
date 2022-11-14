// Fill out your copyright notice in the Description page of Project Settings.


#include "SafeShutDownGameInstance.h"
#include "MainGameClass.h"

// Constructor
USafeShutDownGameInstance::USafeShutDownGameInstance()
{
	// Sets the main game mode pointer to null by default
	m_pMainGameObject = nullptr;
}

// Destructor
USafeShutDownGameInstance::~USafeShutDownGameInstance()
{
}

// Mandatory Override to avoid error
void USafeShutDownGameInstance::Init()
{
	Super::Init();
}

// Mandatory Override to avoid error
void USafeShutDownGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

// Shuts down the game safely
void USafeShutDownGameInstance::Shutdown()
{
	// Sorts out objects before shutdown to prevent any crashes
	m_pMainGameObject->safeExitGame();

	// Carries out regular shut down
	UGameInstance::Shutdown();
}

// Sets the reference to the base game object
void USafeShutDownGameInstance::setMainGameModeReference( AMainGameClass* mainGameObject )
{
	// Sets the main game mode reference
	m_pMainGameObject = mainGameObject;
}
