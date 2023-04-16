// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyGrid.generated.h"

UCLASS()
class UESPACEINVADERS_API AEnemyGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	static FBox GetChildBounds(const class USceneComponent* ParentComponent);

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

	bool IsWorldOut(const FBox& Bounds) const;

	TArray<AActor*> AllEnemies;

	class AUESpaceInvadersGameMode* Mode;

	int32 Cols;
	int32 Rows;
	FVector Direction;
	int32 MoveSpeed;
};
