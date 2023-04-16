// Fill out your copyright notice in the Description page of Project Settings.


#include "UFO.h"
#include "UESpaceInvadersTypes.h"
#include "UESpaceInvadersGameMode.h"

// Sets default values
AUFO::AUFO()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> UFOMesh(TEXT("/Game/Geometry/Meshes/UFO_Mesh.UFO_Mesh"));
	UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UFOMesh"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	StaticMeshComponent->SetStaticMesh(UFOMesh.Object);
	StaticMeshComponent->AddLocalOffset(FVector::ZAxisVector * -50.0f);
	RootComponent = StaticMeshComponent;

	MoveDirection = FVector::YAxisVector;
	MoveSpeed = 1000.0f;
	FlyingRate = 2.0f;
}

uint8 AUFO::GetTeam() const
{
	return ETeam::Enemy;
}

// Called when the game starts or when spawned
void AUFO::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		Mode = Cast<AUESpaceInvadersGameMode>(World->GetAuthGameMode());
		RestTimer();
	}
}

void AUFO::FlyingTimerExpired() {
	IsFlying = true;
}

// Called every frame
void AUFO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFlying)
	{
		const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
		RootComponent->MoveComponent(Movement, FRotator::ZeroRotator, false);
		FBox BoundBox = RootComponent->Bounds.GetBox();

		if (BoundBox.Min.Y > Mode->WorldBounds.Max.Y + 500)
		{
			IsFlying = false;
			RestTimer();
		}
	}
}

void AUFO::RestTimer()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(TimerHandle_FlyingTimerExpired, this, &AUFO::FlyingTimerExpired, FlyingRate);

		FVector SpawnLocation(750, Mode->WorldBounds.Min.Y - 500, 0.0f);
		SetActorLocation(SpawnLocation);
	}
}
