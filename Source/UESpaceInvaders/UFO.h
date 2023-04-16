// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamInterface.h"
#include "UFO.generated.h"

UCLASS()
class UESPACEINVADERS_API AUFO : public AActor, public ITeamInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUFO();

	uint8 GetTeam() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void FlyingTimerExpired();
	void RestTimer();

	float FlyingRate;

	FTimerHandle TimerHandle_FlyingTimerExpired;
	bool IsFlying;
	FVector MoveDirection;
	float MoveSpeed;
	class AUESpaceInvadersGameMode* Mode;
};
