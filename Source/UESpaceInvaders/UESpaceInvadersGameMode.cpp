// Copyright Epic Games, Inc. All Rights Reserved.

#include "UESpaceInvadersGameMode.h"
#include "UESpaceInvadersPawn.h"

AUESpaceInvadersGameMode::AUESpaceInvadersGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AUESpaceInvadersPawn::StaticClass();
}

