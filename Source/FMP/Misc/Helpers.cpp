#include "Helpers.h"
#include "cmath"
#include "Runtime/Core/Public/Containers/UnrealString.h"

// Function to convert a time given in seconds as a float to a readable string in Minutes:Seconds.Miliseconds format
FString convertToTimeFormattedString( float time )
{
	// Gets the time as milliseconds
	int milliseconds = ( std::floor( time * 1000 ) ) - ( std::floor( time ) * 1000 );

	// Rounds the time to the nearest second
	int roundedTime = std::floor( time );

	// Gets number of seconds from the time
	int seconds = roundedTime % 60;

	// Gets number of minutes from the time
	int minutes = roundedTime / 60;

	// String to store the time formatted as a string
	FString timeString;

	// Adds the minutes to the string
	// Adds zeros if the number is less than 10 so that the format stays the same
	if( minutes < 10 )
	{
		timeString = "0" + FString::FromInt( minutes );
	}
	else
	{
		timeString = FString::FromInt( minutes );
	}	

	// Adds the seconds to the string
	// Adds zeros if the number is less than 10 so that the format stays the same
	if( seconds < 10 )
	{
		timeString += ":0" + FString::FromInt( seconds );
	}
	else
	{
		timeString += ":" + FString::FromInt( seconds );
	}

	// Adds the millseconds to the string
	// Adds zeros if the number is less than 100 so that the format stays the same
	if( milliseconds < 10 )
	{
		timeString += ".00" + FString::FromInt( milliseconds );
	}
	else if( milliseconds < 100 )
	{
		timeString += ".0" + FString::FromInt( milliseconds );
	}
	else
	{
		timeString += "." + FString::FromInt( milliseconds );
	}
	
	// Returns the string
	return timeString;
}

// Function to return a reference to a blueprint class from a given file path
TSoftClassPtr<UObject> getBPClass( const char* classPath )
{
	// Gets and returns reference to the given object ( Found Here https://forums.unrealengine.com/t/constructorhelpers-fclassfinder-outside-constructor/39509/2 )
	return TSoftClassPtr<UObject>( FSoftObjectPath( FString( classPath ) ) );
}
