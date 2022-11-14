// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward class declaration
class UFMPSaveGame;

/**
 * 
 */
class FMP_API SaveManager
{
private:
	FString*			m_pFileToAccess;	// String to control which save file is being loaded and saved from
	TArray<FTransform>*	m_pGhostTransforms;	// Array to store the transform of the currently loaded ghost
	bool				m_hasChanged;		// Stores whether the save data has been modified or not
	float				m_lapTime;			// Float to store the loaded laptime

	// Loads laptime from the save file
	void loadLapTime();

	// Loads ghost transforms from the save file
	void loadGhostTransforms();

	// Load data from save file
	void loadAllData();

	// Stores laptime data in the save file ready to be written
	void storeLapTimeData( UFMPSaveGame* saveFile );

	// Stores ghost data in the save file ready to be written
	void storeGhostData( UFMPSaveGame* saveFile );

public:
	// Constructor
	SaveManager( FString* fileToAccess );

	// Destructor
	~SaveManager();

	// Sets the laptime that will later be saved to the save file
	void setTime( float lapTime );

	// Gets the laptime that has been loaded from the save file
	float getTime();

	// Sets a ghost transform that will later be saved to the save file
	void setGhostTransform( TArray<FTransform>* transforms );

	// Gets a ghost transform that has been loaded from the save file
	TArray<FTransform>* getGhostTransform();

	// Gets whether the save data has been changed
	const bool getHasChanged() const;

	// Saves all data the save files
	void save();
};
