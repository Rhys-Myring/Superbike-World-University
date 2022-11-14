#pragma once

// File to store common helper functions

// Forward class declarations
template<typename T> class TSoftClassPtr;
class FString;
class UObject;
class UWorld;

// Templated function to delete pointers safely
template<typename T>
void safeDelete( T*& pointer )
{
	// Checks if the pointer is null or not
	if( pointer )
	{
		// Deletes the pointer
		delete pointer;

		// Sets the pointer to null
		pointer = nullptr;
	}
}

// Templated function to delete arrays from the heap safely
template<typename T>
void safeDeleteArray( T*& arrayPointer )
{
	// Checks if the array is null or not
	if( arrayPointer )
	{
		// Deletes the array
		delete [] arrayPointer;

		// Sets the pointer to the start of the array to null
		arrayPointer = nullptr;
	}
}

// Function to convert a time given in seconds as a float to a readable string in Minutes:Seconds.Miliseconds format
FString convertToTimeFormattedString( float time );

// Function to return a reference to a blueprint class from a given file path
TSoftClassPtr<UObject> getBPClass( const char* classPath );