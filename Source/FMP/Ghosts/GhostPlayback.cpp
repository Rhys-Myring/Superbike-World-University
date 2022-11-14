// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostPlayback.h"
#include "FMP/Misc/Constants.h"
#include "Math/UnrealMathUtility.h"

// Constructor
GhostPlayback::GhostPlayback()
	: m_ghostIndex( 0 )
	, m_timer( 0.0f )
{
	// Initialises the pointers as null
	m_pGhostObject = nullptr;
	m_pGhostBeingPlayed = nullptr;
}

// Destructor
GhostPlayback::~GhostPlayback()
{
}

// Setters
void GhostPlayback::setGhostBeingPlayed( TArray<FTransform>* ghostPlayback )
{
	m_pGhostBeingPlayed = ghostPlayback;
}

void GhostPlayback::setGhostObject( AActor* ghostObject )
{
	m_pGhostObject = ghostObject;
}

// Getter
TArray<FTransform>* GhostPlayback::getGhostBeingPlayed()
{
	return m_pGhostBeingPlayed;
}


// Restarts the playback of the current ghost
void GhostPlayback::restart()
{
	m_ghostIndex = 0;
	m_timer = 0.0f;
}

// Update function
void GhostPlayback::update( float deltaTime )
{
	// Sets the intial position and rotation of the ghost
	if( m_ghostIndex == 0 && m_pGhostBeingPlayed->Num() >= 1 )
	{
		m_pGhostObject->SetActorRotation( ( *m_pGhostBeingPlayed )[m_ghostIndex].GetRotation().Rotator() );
		m_pGhostObject->SetActorLocation( ( *m_pGhostBeingPlayed )[m_ghostIndex].GetLocation() );

		m_ghostIndex++;
	}

	// Lerps the ghost from the current transform to the next one
	if( m_ghostIndex < m_pGhostBeingPlayed->Num() )
	{
		lerpToNextTransform( &( *m_pGhostBeingPlayed )[m_ghostIndex - 1], &( *m_pGhostBeingPlayed )[m_ghostIndex] );
	}

	// Increases the index when the time interval has been reached
	if( m_timer == k_ghostTimeInterval )
	{
		m_ghostIndex++;
		m_timer = 0.0f;
	}

	// Increases timer
	m_timer += deltaTime;

	// Clamps the timer to the ghost interval
	m_timer = FMath::Clamp( m_timer, 0.0f, k_ghostTimeInterval );
}

// Lerps the Ghost's position and rotation towards the next stored point
void GhostPlayback::lerpToNextTransform( FTransform* startTransform, FTransform* endTransform )
{
	// Gets starting and ending positions
	FVector startPos = startTransform->GetLocation();
	FVector endPos = endTransform->GetLocation();
	
	// Gets starting and ending rotations
	FRotator startRot = startTransform->GetRotation().Rotator();
	FRotator endRot = endTransform->GetRotation().Rotator();

	/* Checks whether the absolute distance between the current and next Yaw is more than half a turn (180 Degrees) 
	   For example if the ghost is going from -179 to 178 Degrees, this is only a change of 3 degrees in reality as
	   -179 and 181 are the same amount from the start point but the engine sees this as 357 degrees and therefore spins the
	   ghost all the way around, this check alters the starting value by adding or subtracting 360 degrees to stop this from 
	   happening */
	if( FMath::Abs( startRot.Yaw - endRot.Yaw ) > k_halfTurn )
	{
		if( startRot.Yaw > endRot.Yaw )
		{
			startRot.Yaw -= k_fullTurn;
		}
		else
		{
			startRot.Yaw += k_fullTurn;
		}
	}

	// Lerps the ghost position to the next stored position
	FVector newPosition;
	newPosition.X = FMath::Lerp<float>( startPos.X, endPos.X, m_timer / k_ghostTimeInterval );
	newPosition.Y = FMath::Lerp<float>( startPos.Y, endPos.Y, m_timer / k_ghostTimeInterval );
	newPosition.Z = FMath::Lerp<float>( startPos.Z, endPos.Z, m_timer / k_ghostTimeInterval );

	// Lerps the ghost rotation to the next stored rotation
	FRotator newRotation;
	newRotation.Pitch = FMath::Lerp<float>( startRot.Pitch, endRot.Pitch, m_timer / k_ghostTimeInterval );
	newRotation.Yaw = FMath::Lerp<float>( startRot.Yaw, endRot.Yaw, m_timer / k_ghostTimeInterval );
	newRotation.Roll = FMath::Lerp<float>( startRot.Roll, endRot.Roll, m_timer / k_ghostTimeInterval );

	// Sets the new location
	m_pGhostObject->SetActorLocation( newPosition );

	// Sets new rotation
	m_pGhostObject->SetActorRotation( newRotation );
}