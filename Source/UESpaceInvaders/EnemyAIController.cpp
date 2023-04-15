// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "UESpaceInvadersTypes.h"
#include "UESpaceInvadersProjectile.h"
#include "UESpaceInvaders.h"
#include <Kismet/GameplayStatics.h>

AEnemyAIController::AEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	GunOffset = FVector(-90.f, 0.f, 0.f);
	FireRate = 5.f;
	bCanFire = false;
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanFire)
	{
		const FVector SpawnLocation = GetPawn()->GetActorLocation();//+ GunOffset;

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			auto* Projectile = World->SpawnActor<AUESpaceInvadersProjectile>(SpawnLocation, FRotator::ZeroRotator);
			Projectile->InitProjectile(-FVector::XAxisVector, ETeam::Enemy);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemyAIController::ShotTimerExpired, FireRate);

		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetPawn()->GetActorLocation());
		}
	}
}

void AEnemyAIController::ShotTimerExpired()
{
	bCanFire = true;
}
