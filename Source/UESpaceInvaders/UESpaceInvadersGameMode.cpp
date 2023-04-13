// Copyright Epic Games, Inc. All Rights Reserved.

#include "UESpaceInvadersGameMode.h"
#include "UESpaceInvaders.h"
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

	UpdateWorldBounds();

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		for (int x = 0; x < 5; ++x) {
			for (int y = -5; y <= 5; ++y) {
				FVector SpawnLocation(x * (100 + 30), y * (100 + 30), 220.f);
				auto* Enemy = World->SpawnActor<AEnemy>(SpawnLocation, FRotator::ZeroRotator);
				AllEnemies.Add(Enemy);
			}
		}
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
		UE_LOG(LogUESpaceInvaders, Warning, TEXT("Camera location %s"), *CamLocation.ToString());
		UE_LOG(LogUESpaceInvaders, Warning, TEXT("Distance from ground %f"), DistanceFromGround);
		float Alpha = FMath::DegreesToRadians(PController->PlayerCameraManager->GetFOVAngle() / 2);
		float MaxVisibleDistance = (DistanceFromGround / FMath::Cos(Alpha)) * FMath::Sin(Alpha);

		Points.Add(FVector(CamLocation.X+MaxVisibleDistance,CamLocation.Y+MaxVisibleDistance,PlayerLocation.Z));
		Points.Add(FVector(CamLocation.X-MaxVisibleDistance,CamLocation.Y-MaxVisibleDistance,PlayerLocation.Z));

		WorldBounds = FBox(Points);
	}
}
