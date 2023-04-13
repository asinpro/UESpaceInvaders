// Copyright Epic Games, Inc. All Rights Reserve

#include "UESpaceInvadersProjectile.h"
#include "UESpaceInvaders.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "UESpaceInvadersTypes.h"

AUESpaceInvadersProjectile::AUESpaceInvadersProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileMesh->SetCollisionObjectType(COLLISION_PROJECTILE);
	ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

uint8 AUESpaceInvadersProjectile::GetTeam() const {
	return TeamType;
}

void AUESpaceInvadersProjectile::SetTeam(uint8 Team)
{
	TeamType = Team;
}

void AUESpaceInvadersProjectile::NotifyActorBeginOverlap(class AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogUESpaceInvaders, Warning, TEXT("Begin overlap"));

	//if (!bInitialized)
	//{
	//	return;
	//}

	//if (HitActors.Find(OtherActor) != INDEX_NONE)
	//{
	//	return;
	//}
	//HitActors.AddUnique(OtherActor);

	//const AStrategyChar* HitChar = Cast<AStrategyChar>(OtherActor);
	if (OnEnemyTeam(this, OtherActor))
	{
		UE_LOG(LogUESpaceInvaders, Warning, TEXT("Hit enemy"));
	//	FHitResult PawnHit;
	//	PawnHit.Actor = MakeWeakObjectPtr(const_cast<AStrategyChar*>(HitChar));
	//	PawnHit.Component = HitChar->GetCapsuleComponent();
	//	PawnHit.bBlockingHit = true;
	//	PawnHit.Location = PawnHit.ImpactPoint = GetActorLocation();
	//	PawnHit.Normal = PawnHit.ImpactNormal = -MovementComp->Velocity.GetSafeNormal();

	//	OnHit(PawnHit);
	}
}

bool AUESpaceInvadersProjectile::OnEnemyTeam(const AActor* ActorA, const AActor* ActorB)
{
	const ITeamInterface* TeamA = Cast<const ITeamInterface>(ActorA);
	const ITeamInterface* TeamB = Cast<const ITeamInterface>(ActorB);

	return (TeamA != nullptr) && (TeamB != nullptr) && (TeamA->GetTeam() != TeamB->GetTeam());
}
