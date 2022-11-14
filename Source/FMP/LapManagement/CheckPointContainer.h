// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointContainer.generated.h"

// Forward class declarations
class ABike;
class ATriggerBox;

UCLASS()
class FMP_API ACheckPointContainer : public AActor
{
	GENERATED_BODY()

	// Adds a editable property for the array of checkpoints so they can be assigned through the editor
	UPROPERTY( EditAnywhere, Category = "CheckPoints" ) TArray<ATriggerBox*> m_checkPoints;
	
public:	
	// Sets default values for this actor's properties
	ACheckPointContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter so other objects can access the checkpoints
	const ATriggerBox* getCheckPoint( int index ) const;

	// Getter so other objects can access the array of checkpoints
	const TArray<ATriggerBox*>* getCheckPointArray() const;

};
