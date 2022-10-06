// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterTestGameMode.h"
#include "ShooterTestHUD.h"
#include "ShooterTest/Character/ShooterTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterTestGameMode::AShooterTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterTestHUD::StaticClass();
}
