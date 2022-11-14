// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostManager.h"
#include "GhostPlayback.h"
#include "GhostRecorder.h"

// Constructor
GhostManager::GhostManager()
{
	// Creates ghost playback object
	m_pGhostPlayback = new GhostPlayback;

	// Creates ghost recorder object
	m_pGhostRecorder = new GhostRecorder;
}

// Destructor
GhostManager::~GhostManager()
{
}

// Getter
TArray<FTransform>* GhostManager::getRecordedGhostTransform()
{
	return m_pGhostRecorder->getRecordedGhostTransform();
}

// Setters
void GhostManager::setPlayerObject( AActor* playerObject )
{
	m_pGhostRecorder->setPlayerObject( playerObject );
}

void GhostManager::setGhostBeingPlayed( TArray<FTransform>* ghostPlayback )
{
	m_pGhostPlayback->setGhostBeingPlayed( ghostPlayback );
}

void GhostManager::setGhostObject( AActor* ghostObject )
{
	m_pGhostPlayback->setGhostObject( ghostObject );
}

// Starts ghost recording
void GhostManager::startRecordingGhost()
{
	m_pGhostRecorder->startRecording();
}

// Stops ghost recording
void GhostManager::stopRecordingGhost()
{
	m_pGhostRecorder->stopRecording();
}

// Resets the ghosts that are being recorded and played back
void GhostManager::resetGhosts()
{
	// Restarts the playback of the current ghost
	m_pGhostPlayback->restart();

	// Starts the ghost recording
	m_pGhostRecorder->startRecording();
}

// Swaps the array being recorded and the array being played back
void GhostManager::swapGhostArrays()
{
	TArray<FTransform>* temp = m_pGhostPlayback->getGhostBeingPlayed();
	m_pGhostPlayback->setGhostBeingPlayed( m_pGhostRecorder->getRecordedGhostTransform() );
	m_pGhostRecorder->setRecordedGhostTransform( temp );
}

// Update function
void GhostManager::update( float deltaTime )
{
	// Updates the ghost playback object
	m_pGhostPlayback->update( deltaTime );

	// Updates the ghost recorder object
	m_pGhostRecorder->update( deltaTime );
}
