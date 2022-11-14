// Don't put includes here as it breaks intellisense

#include "MenuInputHandler.h"
#include "FMP/MainGameClasses/MainGameClass.h"
#include "FMP/Menu/MenuManager.h"

// Constructor
AMenuInputHandler::AMenuInputHandler()
	: m_pMenuManager( nullptr )
{
 	// Set this pawn to not tick every frame
	PrimaryActorTick.bCanEverTick = false;
}

// Destructor
AMenuInputHandler::~AMenuInputHandler()
{
}

// Called when the game starts or when spawned
void AMenuInputHandler::BeginPlay()
{
	Super::BeginPlay();

	// Gets the menu manager from the base game class
	m_pMenuManager = static_cast<AMainGameClass*>( GetWorld()->GetAuthGameMode() )->getMenuManager();
}

// Called to bind functionality to input
void AMenuInputHandler::SetupPlayerInputComponent(UInputComponent* inputComponent )
{
	Super::SetupPlayerInputComponent( inputComponent );

	// Binds methods to the different menu input actions
	inputComponent->BindAction( "MenuProceed", IE_Pressed, this, &AMenuInputHandler::menuProceed );
	inputComponent->BindAction( "MenuBack", IE_Pressed, this, &AMenuInputHandler::menuBack );
	inputComponent->BindAction( "MenuUp", IE_Pressed, this, &AMenuInputHandler::menuUp );
	inputComponent->BindAction( "MenuDown", IE_Pressed, this, &AMenuInputHandler::menuDown );	
	inputComponent->BindAction( "MenuLeft", IE_Pressed, this, &AMenuInputHandler::menuLeft );
	inputComponent->BindAction( "MenuRight", IE_Pressed, this, &AMenuInputHandler::menuRight );
}

// Proceeds the current menu
void AMenuInputHandler::menuProceed()
{
	// Proceeds the current menu
	m_pMenuManager->menuProceed();
}

// Goes back from the current menu
void AMenuInputHandler::menuBack()
{
	// Goes back from the current menu
	m_pMenuManager->menuBack();
}

// Goes up a selection in the menu
void AMenuInputHandler::menuUp()
{
	// Goes up a selection in the menu
	m_pMenuManager->menuUp();
}

// Goes down a selection in the menu
void AMenuInputHandler::menuDown()
{
	// Goes down a selection in the menu
	m_pMenuManager->menuDown();
}

// Goes left a selection in the menu
void AMenuInputHandler::menuLeft()
{
	// Goes left a selection in the menu
	m_pMenuManager->menuLeft();
}

// Goes right a selection in the menu
void AMenuInputHandler::menuRight()
{
	// Goes right a selection in the menu
	m_pMenuManager->menuRight();
}

