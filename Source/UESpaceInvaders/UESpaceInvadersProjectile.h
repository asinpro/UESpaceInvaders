// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamInterface.h"
#include "UESpaceInvadersProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class AUESpaceInvadersProjectile : public AActor, public ITeamInterface
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AUESpaceInvadersProjectile();

	void InitProjectile(const FVector& Direction, uint8 Team);

	/** Function to handle the projectile hitting something */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	uint8 GetTeam() const override;

private:
	static bool OnEnemyTeam(const AActor* ActorA, const AActor* ActorB);

	uint8 TeamType;
};

