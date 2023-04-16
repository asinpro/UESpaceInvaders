// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGrid.h"
#include "Enemy.h"
#include "UESpaceInvadersGameMode.h"
#include "UESpaceInvaders.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyGrid::AEnemyGrid()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PrimaryActorTick.bCanEverTick = true;

	Rows = 5;
	Cols = 11;
	AllEnemies.Reserve(Rows * Cols);

	Direction = FVector::YAxisVector;
	MoveSpeed = 500.0f;
}

// Called when the game starts or when spawned
void AEnemyGrid::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		Mode = Cast<AUESpaceInvadersGameMode>(World->GetAuthGameMode());

		int32 ColIndex = Cols >> 1;
		for (int x = 0; x < Rows; ++x) {
			for (int y = -ColIndex; y <= ColIndex; ++y) {
				FVector SpawnLocation(x * (100 + 30), y * (100 + 30), 0.0f);
				AEnemy* Enemy = World->SpawnActor<AEnemy>(SpawnLocation, FRotator::ZeroRotator);
				Enemy->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				Enemy->OnDestroyed.AddDynamic(this, &AEnemyGrid::OnEnemyDestroyed);
				AllEnemies.Add(Enemy);
			}
		}
	}
}

void AEnemyGrid::OnEnemyDestroyed(AActor* DestroyedActor)
{
	AllEnemies.Remove(DestroyedActor);
}

void AEnemyGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(Direction * MoveSpeed * DeltaTime);

	FVector Center, BoxExtent;
	UGameplayStatics::GetActorArrayBounds(AllEnemies, false, Center, BoxExtent);
	FBox BoundBox = FBox::BuildAABB(Center, BoxExtent);

	UKismetSystemLibrary::DrawDebugBox(this, BoundBox.GetCenter(), BoundBox.GetExtent(), FLinearColor::Red);

	if (IsWorldOut(BoundBox))
	{
		FVector Offset = Direction * (Mode->WorldBounds.GetExtent() - BoundBox.GetExtent());

		SetActorLocation(GetActorLocation() * FVector::XAxisVector + Offset);
		AddActorWorldOffset(FVector::XAxisVector * -30);

		Direction *= -1;
	}
}

bool AEnemyGrid::IsWorldOut(const FBox& BoundBox) const {
	return Direction.Y < 0 && BoundBox.Min.Y <= Mode->WorldBounds.Min.Y
		|| Direction.Y > 0 && BoundBox.Max.Y >= Mode->WorldBounds.Max.Y;
}
