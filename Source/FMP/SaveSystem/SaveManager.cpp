// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "FMP/Misc/Constants.h"
#include "FMP/Misc/Helpers.h"
#include "FMPSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Constructor
SaveManager::SaveManager( FString* fileToAccess )
	: m_pFileToAccess( fileToAccess )
	, m_hasChanged( false )
	, m_lapTime( 0.0f )
{
	// Initialises the ghost transforms array and preallocates the maximum size
	m_pGhostTransforms = new TArray<FTransform>();
	m_pGhostTransforms->Empty( k_ghostArraySize );

	// Load data from save file
	loadAllData();
}

// Destructor
SaveManager::~SaveManager()
{
}

// Loads laptime from the save file
void SaveManager::loadLapTime()
{
	// Finds the save game object
	if( UFMPSaveGame* loadedSaveFile = Cast<UFMPSaveGame>( UGameplayStatics::LoadGameFromSlot( *m_pFileToAccess, k_slotIndex ) ) )
	{
		// If the object is successfully found, sets the laptime to what is stored in the file
		m_lapTime = loadedSaveFile->m_time;
	}
}

// Loads ghost transforms from the save file
void SaveManager::loadGhostTransforms()
{
	// Finds the save game object
	if( UFMPSaveGame* loadedSaveFile = Cast<UFMPSaveGame>( UGameplayStatics::LoadGameFromSlot( *m_pFileToAccess, k_slotIndex ) ) )
	{ 
		// If the object is successfully found
		// Iterates through the arrays of position and rotation floats and adds them to an array of transforms
		for( int i = 0; i < loadedSaveFile->m_xPositions.Num(); i++ )
		{
			( *m_pGhostTransforms ).Add(FTransform(
				FRotator( loadedSaveFile->m_xRotations[i], loadedSaveFile->m_yRotations[i], loadedSaveFile->m_zRotations[i] ),
				FVector( loadedSaveFile->m_xPositions[i], loadedSaveFile->m_yPositions[i], loadedSaveFile->m_zPositions[i] ),
				FVector() ) );
		}
	}
}

// Load data from save file
void SaveManager::loadAllData()
{
	// Loads the lap time from the save file
	loadLapTime();

	// Loads ghost transforms from save file
	loadGhostTransforms();
}

// Stores laptime data in the save file ready to be written
void SaveManager::storeLapTimeData( UFMPSaveGame* saveObject )
{
	// Sets the laptimes in the save object to those stored in "m_lapTimes"
	saveObject->m_time = m_lapTime;
}

// Stores ghost data in the save file ready to be written
void SaveManager::storeGhostData( UFMPSaveGame* saveObject )
{
	// Empties all the arrays so new data can be stored in them
	saveObject->m_xPositions.Empty();
	saveObject->m_yPositions.Empty();
	saveObject->m_zPositions.Empty();
	saveObject->m_xRotations.Empty();
	saveObject->m_yRotations.Empty();
	saveObject->m_zRotations.Empty();
			
	// Interates through the array of transforms and stores each position and rotation value as a float
	for( int i = 0; i < m_pGhostTransforms->Num(); i++ )
	{
		// Stores each float value 
		saveObject->m_xPositions.Add( ( *m_pGhostTransforms )[i].GetLocation().X );
		saveObject->m_yPositions.Add( ( *m_pGhostTransforms )[i].GetLocation().Y );
		saveObject->m_zPositions.Add( ( *m_pGhostTransforms )[i].GetLocation().Z );
		saveObject->m_xRotations.Add( ( *m_pGhostTransforms )[i].GetRotation().Rotator().Pitch );
		saveObject->m_yRotations.Add( ( *m_pGhostTransforms )[i].GetRotation().Rotator().Yaw );
		saveObject->m_zRotations.Add( ( *m_pGhostTransforms )[i].GetRotation().Rotator().Roll );
	}
}

// Sets the laptime that will later be saved to the save file
void SaveManager::setTime( float lapTime )
{
	// Stores that the file has changed
	m_hasChanged = true;

	// Sets laptime variable
	m_lapTime = lapTime;
}

// Gets the laptime that has been loaded from the save file
float SaveManager::getTime()
{
	return m_lapTime;
}

// Sets a ghost transform that will later be saved to the save file
void SaveManager::setGhostTransform( TArray<FTransform>* transforms )
{
	// Stores that the file has changed
	m_hasChanged = true;

	// Sets ghost transform variable
	m_pGhostTransforms = transforms;
}

// Gets a ghost transform that has been loaded from the save file
TArray<FTransform>* SaveManager::getGhostTransform()
{
	return m_pGhostTransforms;
}

// Gets whether the save data has been changed
const bool SaveManager::getHasChanged() const
{
	return m_hasChanged;
}

// Saves all data the save files
void SaveManager::save()
{
	// Creates a save game object
	if( UFMPSaveGame* saveGameObject = Cast<UFMPSaveGame>( UGameplayStatics::CreateSaveGameObject( UFMPSaveGame::StaticClass() ) ) )
	{
		// Stores laptime data in the save file ready to be written
		storeLapTimeData( saveGameObject );

		// Stores ghost data in the save file ready to be written
		storeGhostData( saveGameObject );

		// Writes all the data to the save file
		UGameplayStatics::SaveGameToSlot( saveGameObject, *m_pFileToAccess, k_slotIndex );
	}
}
