// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayInputHandler.h"
#include "FMP/Bike/Bike.h"
#include "FMP/MainGameClasses/MainGameClass.h"

// Constructor
AGameplayInputHandler::AGameplayInputHandler()
{
	// Sets the bike pointer to null by default
	m_pBikeToControl = nullptr;

	// Set this pawn to not tick every frame
	PrimaryActorTick.bCanEverTick = false;
}

// Destructor
AGameplayInputHandler::~AGameplayInputHandler()
{
}

// Called when the game starts or when spawned
void AGameplayInputHandler::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AGameplayInputHandler::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent( inputComponent );
	
	// Binds methods to the different gameplay input actions and axis
	inputComponent->BindAxis( "Throttle", this, &AGameplayInputHandler::throttle );
	inputComponent->BindAxis( "Brake", this, &AGameplayInputHandler::brake );
	inputComponent->BindAxis( "Steer", this, &AGameplayInputHandler::steer );
	inputComponent->BindAction( "Pause", IE_Pressed, this, &AGameplayInputHandler::pause );
}

// Sets which bike is being controlled
void AGameplayInputHandler::setBikeToControl( ABike* bikeToControl )
{
	m_pBikeToControl = bikeToControl;
}

// Sets bike's braking input
void AGameplayInputHandler::brake( float brakeAxis )
{
	m_pBikeToControl->setBrakeInput( brakeAxis );
}

// Pauses the game
void AGameplayInputHandler::pause()
{
	// Gets the Main game class and pauses the game
	static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() )->pauseGame();
}

// Sets bike's steering input
void AGameplayInputHandler::steer( float steerAxis )
{
	m_pBikeToControl->setSteeringInput( steerAxis );
}

// Sets bike's throttle input
void AGameplayInputHandler::throttle( float throttleAxis )
{
	m_pBikeToControl->setThrottleInput( throttleAxis );
}

