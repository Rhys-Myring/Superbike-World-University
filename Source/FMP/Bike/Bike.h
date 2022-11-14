#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bike.generated.h"

// Forward class declarations
class UAudioComponent;
class UCameraComponent;
class UStaticMeshComponent;
class USpringArmComponent;

UCLASS()
class FMP_API ABike : public APawn
{
	GENERATED_BODY()

private:
	float		m_brakeInput;				// Stores the amount of brake being inputted
	float		m_frictionCoef;				// Stores the coefficient of friction of the object the bike is currently on
	float		m_frontWheelCircumference;	// Stores the circumference of of the front wheel
	float		m_leanAngle;				// Stores the Bike's lean angle
	float		m_rearWheelCircumference;	// Stores the circumference of of the rear wheel
	float		m_soundVolume;				// Stores the Bike sound volume
	float		m_speed;					// Stores the Bike's speed (scalar, so only magnitude)
	float		m_steeringInput;			// Stores the amount of steering being inputted
	float		m_throttleInput;			// Stores the amount of throttle being inputted
	FRotator	m_turningRotation;			// Stores the Bike's turning rotation
	FVector		m_velocity;					// Stores the Bike's total Velocity (Speed and the direction)

	UPROPERTY( EditAnywhere, Category = "Audio Components", meta = ( DisplayName = "Acceleration Audio" ) )
	UAudioComponent* m_pAcceleratingAudio; // Stores the sound that is played when the bike is accelerating

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Acceleration Rate" ) ) 
	float m_accelerationRate; // Stores bike's rate of acceleration

	UPROPERTY( EditAnywhere, Category = "Bike Meshes", meta = ( DisplayName = "Body Mesh" ) )
	UStaticMeshComponent* m_pBodyMesh; // Stores the bike's main body mesh component
	
	UPROPERTY( EditAnywhere, Category = "Camera", meta = ( DisplayName = "Camera" ) )
	UCameraComponent* m_pCamera; // Stores the bike's camera component

	UPROPERTY( EditAnywhere, Category = "Collision Mesh", meta = ( DisplayName = "Collision Mesh" ) )
	UStaticMeshComponent* m_pCollisionMesh; // Stores the mesh that contains the bike's collision

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Deceleration Rate" ) ) 
	float m_decelerationRate; // Stores bike's rate of acceleration

	UPROPERTY( EditAnywhere, Category = "Bike Meshes", meta = ( DisplayName = "Fork Mesh" ) )
	UStaticMeshComponent* m_pForkMesh; // Stores bike's front forks mesh

	UPROPERTY( EditAnywhere, Category = "Bike Parameters|Animations", meta = ( DisplayName = "Front Fork Turning Speed" ) )
	float m_frontForkTurningSpeed; // Bike's front fork visual turning speed

	UPROPERTY( EditAnywhere, Category = "Bike Meshes", meta = ( DisplayName = "Front Wheel Mesh" ) )
	UStaticMeshComponent* m_pFrontWheelMesh; // Stores bike's front wheel mesh

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Front Wheel Radius" ) )
	float m_frontWheelRadius; // Stores bike's front wheel radius

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Height Decrease At Lean" ) ) 
	float m_heightDecreaseAtLean; // Stores how many units the bike should be moved down when leaning to stop it floating

	UPROPERTY( EditAnywhere, Category = "Audio Components", meta = ( DisplayName = "Idle Audio" ) )
	UAudioComponent* m_pIdleAudio; // Stores the sound that is played when the bike is at idle

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Leaning Speed" ) )
	float m_leaningSpeed; // Stores how quickly the bike can get to full lean angle

	UPROPERTY( EditAnywhere, Category = "Bike Parameters|Animations", meta = ( DisplayName = "Maximum Front Fork Angle" ) )
	float m_maxFrontForkAngle; //Stores the maximum angle the front forks can visually turn to

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Maximum Lean Angle" ) )
	float m_maxLeanAngle; // Stores the maximum lean angle that the bike can achieve

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Maximum Speed" ) )
	float m_maxSpeed; // Stores the maximum speed that the bike can achieve

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Maximum Turning Angle" ) )
	float m_maxTurningAngle; // Stores the maximum turning angle that the bike can achieve

	UPROPERTY( EditAnywhere, Category = "Bike Meshes", meta = ( DisplayName = "Rear Wheel Mesh" ) )
	UStaticMeshComponent* m_pRearWheelMesh; // Stores bike's rear wheel mesh

	UPROPERTY( EditAnywhere, Category = "Bike Parameters", meta = ( DisplayName = "Rear Wheel Radius" ) )
	float m_rearWheelRadius; // Stores bike's rear wheel radius

	UPROPERTY( EditAnywhere, Category = "Rider Mesh", meta = ( DisplayName = "Rider Mesh" ) )
	UStaticMeshComponent* m_pRiderMesh; // Stores the rider's mesh

	UPROPERTY( EditAnywhere, Category = "Camera", meta = ( DisplayName = "Spring Arm" ) )
	USpringArmComponent* m_pSpringArm; // Stores the bike's spring arm component

	// Applies custom gravity effect as the base one causes issues
	void applyGravity( float deltaTime );

	// Sets the bike's lean angle based on the player's inputs
	void calculateLeanAndTurning( float deltaTime );

	// Calculates the bike's new speed
	void calculateSpeed( float deltaTime );

	// Detects the physics material that the bike is currently on
	void detectTerrain();

	// Intitalises all the bike's components
	void intitaliseAllComponents();

	// Intitalises the bike's audio components
	void intitaliseAudioComponents();

	// Intitalises the bike's body mesh
	void initialiseBodyMesh();

	// Intitalises the bike's camera component
	void intitaliseCamera();

	// Intitalises the bike's collision mesh
	void initialiseCollisionMesh();
	
	// Intitalises the bike's front fork mesh
	void intitaliseFrontForkMesh();

	// Intitalises the bike's front wheel mesh
	void intitaliseFrontWheelMesh();

	// Intitalises the bike's rear wheel mesh
	void intitaliseRearWheelMesh();

	// Intitalises the rider's mesh
	void intitaliseRiderMesh();

	// Stops the rotation going beyond what is expected
	void keepValuesValid();

	// Plays an appropriate engine sound based on how the bike is accelerating
	void playSound();

	// Updates bike's wheel and handle bar rotations
	void updateAnimations( float deltaTime );

	// Updates bike's position and rotation
	void updatePositionAndTurningRotation( float deltaTime );

public:
	// Constructor
	ABike();

	// Destructor
	~ABike();

	// Stops the bike making sound or moving when paused 
	void pause( bool paused );

	// Sets the bike's brake input based on the input axis
	void setBrakeInput( float brakeInput );

	// Sets the bike's steering input based on the input axis
	void setSteeringInput( float steeringInput );

	// Sets the bike's throttle input based on the input axis
	void setThrottleInput( float throttleInput );

	// Sets the bike's volume based on the inputted float
	void setVolume( float volume );

	// Updates the bike object
	void update( float DeltaTime );
};