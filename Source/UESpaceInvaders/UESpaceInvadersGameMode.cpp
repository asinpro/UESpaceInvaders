// Copyright Epic Games, Inc. All Rights Reserved.

#include "UESpaceInvadersGameMode.h"
#include "UESpaceInvaders.h"
#include "UESpaceInvadersPawn.h"
#include "EnemyGrid.h"

AUESpaceInvadersGameMode::AUESpaceInvadersGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AUESpaceInvadersPawn::StaticClass();
}

void AUESpaceInvadersGameMode::StartPlay()
{
	Super::StartPlay();

	UpdateWorldBounds();

	if (UWorld* World = GetWorld()) {
		World->SpawnActor<AEnemyGrid>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
}

void AUESpaceInvadersGameMode::UpdateWorldBounds()
{
	UWorld* const World = GetWorld();
	if( World != nullptr )	
	{
		auto* PController = World->GetFirstPlayerController();
		auto* PlayerShip = Cast<AUESpaceInvadersPawn>(PController->GetPawn());
		FVector PlayerLocation = PlayerShip->GetActorLocation();

		TArray<FVector> Points;
		FVector const CamLocation = PController->GetViewTarget()->GetActorLocation();
		float DistanceFromGround = CamLocation.Z - PlayerLocation.Z;
		float Alpha = FMath::DegreesToRadians(PController->PlayerCameraManager->GetFOVAngle() / 2);
		float MaxVisibleDistance = (DistanceFromGround / FMath::Cos(Alpha)) * FMath::Sin(Alpha);

		Points.Add(FVector(CamLocation.X+MaxVisibleDistance,CamLocation.Y+MaxVisibleDistance,PlayerLocation.Z));
		Points.Add(FVector(CamLocation.X-MaxVisibleDistance,CamLocation.Y-MaxVisibleDistance,PlayerLocation.Z));

		WorldBounds = FBox(Points);
	}
}
