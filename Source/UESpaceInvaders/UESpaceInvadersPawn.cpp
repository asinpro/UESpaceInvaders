// Copyright Epic Games, Inc. All Rights Reserved.

#include "UESpaceInvadersPawn.h"
#include "UESpaceInvadersProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "UESpaceInvadersTypes.h"
#include "UESpaceInvadersGameMode.h"

const FName AUESpaceInvadersPawn::MoveRightBinding("MoveRight");
const FName AUESpaceInvadersPawn::FireBinding("Fire");

AUESpaceInvadersPawn::AUESpaceInvadersPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MoveSpeed = 1000.0f;
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;
}

void AUESpaceInvadersPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction(FireBinding, EInputEvent::IE_Pressed, this, &AUESpaceInvadersPawn::FireStarted);
	PlayerInputComponent->BindAction(FireBinding, EInputEvent::IE_Released, this, &AUESpaceInvadersPawn::FireStopped);
	//PlayerInputComponent->BindKey(EKeys::SpaceBar, EInputEvent::IE_Pressed, this, &AUESpaceInvadersPawn::FireShot);
}

void AUESpaceInvadersPawn::Tick(float DeltaSeconds)
{
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	const FVector MoveDirection = FVector(0.f, RightValue, 0.f);
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr) {
			RootComponent->MoveComponent(Movement, FRotator::ZeroRotator, false);

			auto* Mode = World->GetAuthGameMode<AUESpaceInvadersGameMode>();
			FBox BoundBox = RootComponent->GetLocalBounds().GetBox();
			
			FBox WorldBounds = Mode->WorldBounds.ExpandBy(-FVector::YAxisVector * BoundBox.GetExtent().Y);
			FVector ClampedLocation = WorldBounds.GetClosestPointTo(GetActorLocation());
			SetActorLocation(ClampedLocation);
		}
	}

	if (bCanFire == true)
	{
		const FVector SpawnLocation = GetActorLocation() + GunOffset;

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			auto* Projectile = World->SpawnActor<AUESpaceInvadersProjectile>(SpawnLocation, FRotator::ZeroRotator);
			Projectile->SetTeam(ETeam::Player);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AUESpaceInvadersPawn::ShotTimerExpired, FireRate);

		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}

void AUESpaceInvadersPawn::FireStarted()
{
	bCanFire = bFireStarted = true;
}

void AUESpaceInvadersPawn::FireStopped()
{
	bCanFire = bFireStarted = false;
}

void AUESpaceInvadersPawn::ShotTimerExpired()
{
	bCanFire = bFireStarted;
}

uint8 AUESpaceInvadersPawn::GetTeam() const
{
	return ETeam::Player;
}

