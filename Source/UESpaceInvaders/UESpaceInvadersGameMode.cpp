// Copyright Epic Games, Inc. All Rights Reserved.

#include "UESpaceInvadersGameMode.h"
#include "UESpaceInvadersPawn.h"
#include "Enemy.h"

AUESpaceInvadersGameMode::AUESpaceInvadersGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AUESpaceInvadersPawn::StaticClass();
}

void AUESpaceInvadersGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		for (int y = -2; y <= 2; ++y) {
			for (int x = -2; x <= 2; ++x) {
				FVector SpawnLocation(x * (100 + 10), y * (100 + 10), 210.f);
				World->SpawnActor<AEnemy>(SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
}

