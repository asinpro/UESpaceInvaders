// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UESpaceInvadersGameMode.generated.h"

UCLASS(MinimalAPI)
class AUESpaceInvadersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUESpaceInvadersGameMode();

	void StartPlay() override;

	UPROPERTY(EditAnywhere)
	FBox WorldBounds;

	void AddScore(int32 NewScore);
	int32 GetScore() const;

	int32 GetPlayerLives() const;
private:
	void UpdateWorldBounds();
	void SpawnUFO(class UWorld* World);

	UFUNCTION()
	void OnUFODestroyed(AActor* DestroyedActor);

	int32 Score = 0;
	int32 PlayerLives;
};

