// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterTestGameMode.h"
#include "ShooterTestHUD.h"
#include "ShooterTest/Character/CharacterBase.h"
#include "UObject/ConstructorHelpers.h"

AShooterTestGameMode::AShooterTestGameMode()
	: Super()
{
	HUDClass = AShooterTestHUD::StaticClass();
}
