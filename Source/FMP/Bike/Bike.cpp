// Don't put includes on this line it causes issues

#include "Bike.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/AudioComponent.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "FMP/Misc/Constants.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Constructor
ABike::ABike()
// Sets default values through intialiser list
	: m_accelerationRate( k_defaultAccelerationRate )
	, m_brakeInput( 0.0f )
	, m_frictionCoef( 0.0f )
	, m_decelerationRate( k_defaultDecelerationRate )
	, m_frontForkTurningSpeed( k_defaultForkAnimationSpeed )
	, m_frontWheelRadius( k_defaultFrontWheelRadius )
	, m_heightDecreaseAtLean( k_defaultHeightDecreaseAtLean )
	, m_leanAngle( 0.0f )
	, m_leaningSpeed( k_defaultLeaningSpeed )
	, m_maxFrontForkAngle( k_defaultMaxFrontForkAngle )
	, m_maxLeanAngle( k_defaultMaxLeanAngle )
	, m_maxSpeed( k_defaultMaxSpeed )
	, m_maxTurningAngle( k_defaultMaxTurningAngle )
	, m_rearWheelRadius( k_defaultRearWheelRadius )
	, m_soundVolume( 0.0f )
	, m_speed( 0.0f )
	, m_steeringInput( 0.0f )
	, m_throttleInput( 0.0f )
	, m_turningRotation( FRotator() )
	, m_velocity( FVector() )
{
	// Calculates front wheel circumference
	m_frontWheelCircumference = UKismetMathLibrary::GetPI() * ( m_frontWheelRadius + m_frontWheelRadius );

	// Calculates rear wheel circumference
	m_rearWheelCircumference = UKismetMathLibrary::GetPI() * ( m_rearWheelRadius + m_rearWheelRadius );
	
	// Set this actor to not Tick() every frame
	PrimaryActorTick.bCanEverTick = false;

	// Initialises all the bike's components
	intitaliseAllComponents();
}

// Destructor
ABike::~ABike()
{
}

// Applies custom gravity effect as the base one causes issues
void ABike::applyGravity( float deltaTime )
{
	// Moves body down so that the bike doesn't appear to float off the ground at high lean angles
	m_pBodyMesh->SetRelativeLocation( FVector( m_pBodyMesh->GetRelativeLocation().X, m_pBodyMesh->GetRelativeLocation().Y,
		UKismetMathLibrary::Abs( m_leanAngle / m_maxLeanAngle ) * m_heightDecreaseAtLean ) );

	m_pSpringArm->SetRelativeLocation( FVector( m_pSpringArm->GetRelativeLocation().X, m_pSpringArm->GetRelativeLocation().Y,
		UKismetMathLibrary::Abs( m_leanAngle / m_maxLeanAngle ) * m_heightDecreaseAtLean ) );

	// Adds gravity effect as gravity is disabled, due it not being strong enough and causing weird issues with the physics
	AddActorWorldOffset( FVector( 0.0f, 0.0f, k_gravity * m_pCollisionMesh->GetMass() * deltaTime ), true );
}

// Sets the bike's lean angle based on the player's inputs
void ABike::calculateLeanAndTurning( float deltaTime )
{
	if( m_speed )
	{
		// Smoothly calculates lean angle based on friction coefficient and current turning input
		m_leanAngle = FMath::FInterpTo( m_leanAngle,
			( m_steeringInput * m_maxLeanAngle ), deltaTime, k_baseInputModifier + FMath::Abs( m_steeringInput ) );

		// Sets turning rotation based on the bike's lean angle and the steering input from the player
		m_turningRotation.Yaw = FMath::Abs( m_steeringInput ) * m_leanAngle;
	}
	else
	{
		// Smoothly interpolates lean angle towards 0
		m_leanAngle = FMath::FInterpTo( m_leanAngle, 0.0f, deltaTime, k_baseInputModifier + FMath::Abs( m_steeringInput ) );
		
		// Sets turning rotation to 0
		m_turningRotation.Yaw = 0.0f;

		SetActorRotation( FRotator( GetActorRotation().Pitch, GetActorRotation().Yaw, m_leanAngle ) );
	}
}

// Calculates the bike's new speed
void ABike::calculateSpeed( float deltaTime )
{
	// Accelerates bike based on how much throttle is applied
	if( m_throttleInput > 0.0f )
	{
		// Adds acceleration multiplied by the axis input to the object's speed (Multiplied by delta time so it's time compensated)
		m_speed += m_throttleInput * m_accelerationRate * deltaTime;
	}
	else
	{
		// Applies engine braking to the bike if no throttle is applied
		m_speed -= m_decelerationRate * deltaTime;
	}

	// Decelerates bike based on the brake input
	m_speed -= m_brakeInput * m_decelerationRate * deltaTime;

	// Clamps speed between its min & max based on the current terrain
	m_speed = FMath::Clamp( m_speed, 0.0f, m_maxSpeed * ( m_frictionCoef + k_baseTerrainMultiplier ) );
}

// Detects the physics material that the bike is currently on
void ABike::detectTerrain()
{
	// Creates variable to store the result of the hit
	FHitResult objectHit;
	
	// Ignores the current actor
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor( this );

	// Draws ray to detect what is below the bike
	bool success = 
		GetWorld()->LineTraceSingleByChannel( objectHit, GetActorLocation(), GetActorLocation() + FVector( 0.0f, 0.0f, -1000.0f ),
		ECollisionChannel::ECC_WorldStatic, queryParams, FCollisionResponseParams() );

	// If anything has been hit
	if( success )
	{
		// Gets the physical material of the object below the bike
		UPhysicalMaterial* physicsMaterial = objectHit.GetComponent()->BodyInstance.GetSimplePhysicalMaterial();

		// Sets the new friction coefficent
		m_frictionCoef = physicsMaterial->Friction;
	}
}

// Stops the rotation going beyond what is expected
void ABike::keepValuesValid()
{
	// Stops bike from moving or rotating oddly because of the curbs or terrain
	m_pCollisionMesh->SetPhysicsAngularVelocityInDegrees( FVector( 0.0f, 0.0f, 0.0f ) );
	m_pCollisionMesh->SetPhysicsLinearVelocity( FVector( 0.0f, 0.0f, 0.0f ) );

	// If Bike's pitch goes beyond a valid value it's reset
	if( FMath::Abs( GetActorRotation().Pitch ) > k_maxPitch )
	{
		SetActorRotation( FRotator( 0.0f, GetActorRotation().Yaw, GetActorRotation().Roll ) );
	}
}

// Stops the bike making sound or moving when paused 
void ABike::pause( bool paused )
{
	// If being paused
	if( paused )
	{
		// Stops idle audio
		if( m_pIdleAudio->IsPlaying() )
		{
			m_pIdleAudio->Stop();
		}

		// Stops accelerating audio
		if( m_pAcceleratingAudio->IsPlaying() )
		{
			m_pAcceleratingAudio->Stop();
		}

		// Sets the collision mesh to stop simulating physics
		m_pCollisionMesh->SetSimulatePhysics( false );
		
	}
	else
	{
		// Sets the collision mesh to start simulating physics
		m_pCollisionMesh->SetSimulatePhysics( true );
	}
}

// Plays an appropriate engine sound based on how the bike is accelerating
void ABike::playSound()
{
	// Starts playing acceleration sound if bike is accelerating
	if( m_speed > 0.0f )
	{
		if( m_pIdleAudio->IsPlaying() )
		{
			// Stops idle audio component
			m_pIdleAudio->FadeOut( k_fadeInTime, 0.0f );
		}

		// If acceleration isn't playing, it starts playing
		if( !m_pAcceleratingAudio->IsPlaying() )
		{
			m_pAcceleratingAudio->FadeIn( k_fadeInTime, m_soundVolume );
		}
	}
	else
	{
		if( m_pAcceleratingAudio->IsPlaying() )
		{
			// Stops acceleration audio component
			m_pAcceleratingAudio->FadeOut( k_fadeInTime, 0.0f );
		}

		if( !m_pIdleAudio->IsPlaying() )
		{
			// Plays idle sound
			m_pIdleAudio->FadeIn( k_fadeInTime, m_soundVolume );
		}
	}

	// Sets pitch of acceleration sound based on speed
	m_pAcceleratingAudio->SetPitchMultiplier( m_speed / m_maxSpeed );
}

// Intitalises all the bike's components
void ABike::intitaliseAllComponents()
{
	// Intitalises the bike's collision mesh
	initialiseCollisionMesh();

	// Intitalises the bike's body mesh
	initialiseBodyMesh();
	
	// Intitalises the bike's rear wheel mesh
	intitaliseRearWheelMesh();

	// Intitalises the bike's front fork mesh
	intitaliseFrontForkMesh();

	// Intitalises the bike's front wheel mesh
	intitaliseFrontWheelMesh();

	// Intitalises the bike's camera component
	intitaliseCamera();

	// Intitalises the bike's audio components
	intitaliseAudioComponents();

	// Initialiese the rider's mesh component
	intitaliseRiderMesh();
}

// Intitalises the bike's audio components
void ABike::intitaliseAudioComponents()
{
	// Creates idle audio component
	m_pIdleAudio = CreateDefaultSubobject<UAudioComponent>( TEXT( "Idle Audio" ) );

	// Attaches idle audio component to the bike mesh component
	m_pIdleAudio->AttachToComponent( m_pCollisionMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Play idle sound
	m_pIdleAudio->Play();

	// Creates accelerating audio component
	m_pAcceleratingAudio = CreateDefaultSubobject<UAudioComponent>( TEXT( "Acceleration Audio" ) );

	// Attaches accelerating audio component to the bike mesh component
	m_pAcceleratingAudio->AttachToComponent( m_pCollisionMesh, FAttachmentTransformRules::KeepRelativeTransform );
}

// Intitalises the bike's body mesh
void ABike::initialiseBodyMesh()
{
	// Creates static mesh component for the bike's main body
	m_pBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Body Mesh" ) );

	// Attaches the body mesh component to the collision mesh
	m_pBodyMesh->AttachToComponent( m_pCollisionMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets the body mesh to not simulate physics
	m_pBodyMesh->SetSimulatePhysics( false );
}

// Intitalises the bike's camera component
void ABike::intitaliseCamera()
{
	// Creates spring arm component
	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>( TEXT( "Spring Arm Component" ) );

	// Attaches spring arm component to the skeletal mesh component
	m_pSpringArm->AttachToComponent( m_pCollisionMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Creates camera component
	m_pCamera = CreateDefaultSubobject<UCameraComponent>( TEXT( "Camera Component" ) );

	// Attaches camera component to the spring arm
	m_pCamera->AttachToComponent( m_pSpringArm, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets camera position
	FVector cameraPos = FVector( k_defaultCameraX, k_defaultCameraY, k_defaultCameraZ );
	m_pCamera->SetRelativeLocation( cameraPos );
}

// Intitalises the bike's collision mesh
void ABike::initialiseCollisionMesh()
{
	// Creates static mesh component for the bike's collision
	m_pCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Collision Mesh" ) );

	// Attaches collision mesh component to the root of the actor
	m_pCollisionMesh->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets the collision mesh to simulate physics
	m_pCollisionMesh->SetSimulatePhysics( true );

	// Disables gravity as it isn't strong enough and causes strange issues
	m_pCollisionMesh->SetEnableGravity( false );
}

// Intitalises the bike's front fork mesh
void ABike::intitaliseFrontForkMesh()
{
	// Creates static mesh component for the bike's front forks
	m_pForkMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Front Fork Mesh" ) );

	// Attaches the front fork mesh component to the body mesh
	m_pForkMesh->AttachToComponent( m_pBodyMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets the front fork mesh to not simulate physics
	m_pForkMesh->SetSimulatePhysics( false );
}

// Intitalises the bike's front wheel mesh
void ABike::intitaliseFrontWheelMesh()
{
	// Creates static mesh component for the bike's front wheel
	m_pFrontWheelMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Front Wheel Mesh" ) );

	// Attaches the front wheel mesh component to the front fork mesh
	m_pFrontWheelMesh->AttachToComponent( m_pForkMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets the front wheel mesh to not simulate physics
	m_pFrontWheelMesh->SetSimulatePhysics( false );
}

// Intitalises the bike's rear wheel mesh
void ABike::intitaliseRearWheelMesh()
{
	// Creates static mesh component for the bike's rear wheel
	m_pRearWheelMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Rear Wheel Mesh" ) );

	// Attaches the rear wheel mesh component to the body mesh
	m_pRearWheelMesh->AttachToComponent( m_pBodyMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets the rear wheel mesh to not simulate physics
	m_pRearWheelMesh->SetSimulatePhysics( false );
}

// Intitalises the rider's mesh
void ABike::intitaliseRiderMesh()
{
	// Creates static mesh component for the rider
	m_pRiderMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Rider Mesh" ) );

	// Attaches the rider mesh component to the body mesh
	m_pRiderMesh->AttachToComponent( m_pBodyMesh, FAttachmentTransformRules::KeepRelativeTransform );

	// Sets the rider mesh to not simulate physics
	m_pRiderMesh->SetSimulatePhysics( false );
}

// Sets the bike's brake input based on the input axis
void ABike::setBrakeInput( float brakeInput )
{
	m_brakeInput = brakeInput;
}

// Sets the bike's steering input based on the input axis
void ABike::setSteeringInput( float steeringInput )
{
	// Stores the value of the steering input
	m_steeringInput = steeringInput;
}

// Sets the bike's throttle input based on the input axis
void ABike::setThrottleInput( float throttleInput )
{
	// Stores the value of the throttle input
	m_throttleInput = throttleInput;
}

// Sets the bike's volume based on the inputted float
void ABike::setVolume( float volume )
{
	m_soundVolume = volume;
}

// Updates bike's wheel and handle bar rotations
void ABike::updateAnimations( float deltaTime )
{
	// Rotates front wheel ( Bike speed divided by circumference of front wheel )
	m_pFrontWheelMesh->AddLocalRotation(
		FRotator( -( m_speed / m_frontWheelCircumference ), 0.0f, 0.0f ) );

	// Rotates rear wheel ( Bike speed divided by circumference of rear wheel )
	m_pRearWheelMesh->AddLocalRotation(
		FRotator( -( m_speed / m_rearWheelCircumference ), 0.0f, 0.0f ) );

	// Rotates handlebars, front forks and front wheel when steering
	m_pForkMesh->SetRelativeRotation( FRotator( 0.0f, 0.0f, FMath::FInterpTo( m_pForkMesh->GetRelativeRotation().Roll,
		( m_turningRotation.Yaw / m_maxTurningAngle ) * m_maxFrontForkAngle, deltaTime, m_frontForkTurningSpeed ) ) );
}

// Updates bike's position and rotation
void ABike::updatePositionAndTurningRotation( float deltaTime )
{
	// Updates bike's location based on its velocity
	FVector newLocation = GetActorLocation() + ( m_velocity * deltaTime );
	SetActorLocation( newLocation );

	// Update bike's rotation, both lean angle and turning angle
	FRotator newRotation = FRotator( GetActorRotation().Pitch, GetActorRotation().Yaw + 
		( m_turningRotation.Yaw * deltaTime * m_frictionCoef ), m_leanAngle );
	SetActorRotation( newRotation );
}

// Updates the bike object
void ABike::update( float deltaTime )
{
	// Sets velocity to forwards direction multiplied by the speed of the object
	m_velocity = this->GetActorForwardVector() * m_speed;

	if( !m_velocity.IsZero() )
	{
		// Updates bike's location and rotation
		updatePositionAndTurningRotation( deltaTime );
	}

	// Calculates the bike's new speed
	calculateSpeed( deltaTime );

	// Calculates the bike's leaning and turning angle
	calculateLeanAndTurning( deltaTime );

	// Detects the physics material that the bike is currently on
	detectTerrain();

	// Stops the rotation going beyond what is expected
	keepValuesValid();

	// Plays the appropriate engine sound
	playSound();

	// Updates bike's wheel and handle bar rotations
	updateAnimations( deltaTime );

	// Applies custom gravity effect as the base one causes issues
	applyGravity( deltaTime );
}