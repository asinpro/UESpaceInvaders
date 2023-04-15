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

private:
	void UpdateWorldBounds();
};

