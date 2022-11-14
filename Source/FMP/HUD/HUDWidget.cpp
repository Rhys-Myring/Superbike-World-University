// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"

// Constructor
UHUDWidget::UHUDWidget( const FObjectInitializer& ObjectInitializer ) :UUserWidget( ObjectInitializer )
{
	// Sets UProperties to null by default
	BestLapTimeText = nullptr;
	LapTimeText = nullptr;
}

// Destructor
UHUDWidget::~UHUDWidget()
{
}

// Setters
void UHUDWidget::setBestTimeText( FText* bestTimeText )
{
	// Sets best time text
	BestLapTimeText->SetText( *bestTimeText );
}

void UHUDWidget::setLapTimeText( FText* lapTimeText )
{
	// Sets lap time text
	LapTimeText->SetText( *lapTimeText );
}
