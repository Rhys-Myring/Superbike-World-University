// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostRecorder.h"
#include "FMP/Misc/Constants.h"

// Constructor
GhostRecorder::GhostRecorder()
	: m_isRecording( true )
	, m_timer( 0.0f )
{
	// Sets player object as null by default
	m_pPlayerObject = nullptr;

	// Makes array slack the maximum ghost size so memory is pre-allocated 
	// This is so indexes can be added during runtime without slowing the game down
	m_pPlayerPositions = new TArray<FTransform>();
	( * m_pPlayerPositions ).Empty( k_ghostArraySize );
}

// Destructor
GhostRecorder::~GhostRecorder()
{
}

// Getter
TArray<FTransform>* GhostRecorder::getRecordedGhostTransform()
{
	return m_pPlayerPositions;
}

// Setter
void GhostRecorder::setRecordedGhostTransform( TArray<FTransform>* newArray )
{
	m_pPlayerPositions = newArray;
}

void GhostRecorder::setPlayerObject( AActor* playerObject )
{
	m_pPlayerObject = playerObject;
}

// Starts ghost recording
void GhostRecorder::startRecording()
{
	// Sets is recording to true
	m_isRecording = true;

	// Empties the previous ghost data from the array
	m_pPlayerPositions->Reset();

	// Sets the starting position of the player for the ghost
	( *m_pPlayerPositions ).Add( m_pPlayerObject->GetTransform() );
}

// Stops ghost recording
void GhostRecorder::stopRecording()
{
	// Sets is recording to false
	m_isRecording = false;

	// Saves last point
	( *m_pPlayerPositions ).Add( m_pPlayerObject->GetTransform() );
}

// Update function
void GhostRecorder::update( float deltaTime )
{
	// Only records ghost if the maximum size hasn't been reached and if it is being told to record
	if( ( ( *m_pPlayerPositions ).Num() < k_ghostArraySize ) && ( m_isRecording ) )
	{
		// If the time interval that the ghost saves the position at has passed, the position is stored and the time is reset
		if( m_timer >= k_ghostTimeInterval )
		{
			// Stores the current position of the player
			( *m_pPlayerPositions ).Add( m_pPlayerObject->GetTransform() );

			// Resets timer
			m_timer = 0.0f;
		}

		// Increments timer by delta time
		m_timer += deltaTime;

		// Clamps the timer to the ghost interval
		m_timer = FMath::Clamp( m_timer, 0.0f, k_ghostTimeInterval );
	}
}
