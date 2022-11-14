#pragma once

// File to store different constants to avoid magic numbers

// World constants
const float k_gravity = -9.81f;

// Default bike values
const float k_baseInputModifier = 1.0f;
const float k_baseTerrainMultiplier = 0.3f;
const float k_defaultAccelerationRate = 500.0f;
const float k_defaultDecelerationRate = 2000.0f;
const float k_defaultForkAnimationSpeed = 1.5f;
const float k_defaultFrontWheelRadius = 28.5f;
const float k_defaultHeightDecreaseAtLean = -19.5f;
const float k_defaultIdleRPM = 2300.0f;
const float k_defaultLeaningSpeed = 20.0f;
const float k_defaultMaxFrontForkAngle = 10.0f;
const float k_defaultMaxLeanAngle = 45.0f;
const float k_defaultMaxRPM = 12000.0f;
const float k_defaultMaxSpeed = 5000.0f;
const float k_defaultMaxTurningAngle = 40.0f;
const float k_defaultRearWheelRadius = 31.0f;
const float k_maxPitch = 20.0f;

// Default camera values
const float k_defaultCameraX = -41.0f;
const float k_defaultCameraY = 0.0f;
const float k_defaultCameraZ = 123.0f;

// Save values
const int k_slotIndex = 0;

// Ghost values
const int k_ghostArraySize = 3000;
const float k_maximumLapTime = 300.0f;
const float k_ghostTimeInterval = 0.1f;
const float k_halfTurn = 180.0f;
const float k_fullTurn = 360.0f;

// Menu widget row names
const char k_backgroundVideo[15] = "MenuBackground";
const char k_bikeSelectionMenu[18] = "BikeSelectionMenu";
const char k_loadingScreen[14] = "LoadingScreen";
const char k_mainMenu[9] = "MainMenu";
const char k_optionsMenu[12] = "OptionsMenu";
const char k_pauseMenu[10] = "PauseMenu";
const char k_startPage[10] = "StartPage";
const char k_timeTrialMenu[14] = "TimeTrialMenu";
const char k_trackSelectionMenu[19] = "TrackSelectionMenu";

// HUD Widget Path
const char k_headUpDisplayPath[63] = "/Game/blueprintClasses/HUD/widgets/BP_HUDWidget.BP_HUDWidget_C";

// Menu Sound Names
const char k_backSound[9] = "MenuBack";
const char k_proceedSound[12] = "MenuProceed";
const char k_scrollHorizontalSound[21] = "MenuScrollHorizontal";
const char k_scrollVerticalSound[19] = "MenuScrollVertical";

// Menu Z orders
const int k_backgroundVideoZOrder = -1;
const int k_loadingScreenZOrder = 2;

// Menu strings
const char k_showGhostText[16] = "Show Ghost: Yes";
const char k_hideGhostText[15] = "Show Ghost: No";
const char k_playSoundText[14] = "Unmute Sounds";
const char k_muteSoundText[12] = "Mute Sounds";

// HUD strings
const char k_defaultBestLapText[21] = "Best Time: --:--.---";
const char k_defaultLapText[16] = "Time: --:--.---";

// Loading time
const float k_extraLoadingTime = 3.0f;

// Audio Constants
const float k_defaultVolume = 1.0f;
const float k_fadeInTime = 1.0f;