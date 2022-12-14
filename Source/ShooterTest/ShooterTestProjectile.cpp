// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterTestProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AShooterTestProjectile::AShooterTestProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShooterTestProjectile::OnHit);		// set up a notification for when this component hits something blocking
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AShooterTestProjectile::Initialize(float DamageValue, float Speed)
{
	Damage = DamageValue;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
}

void AShooterTestProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && OtherActor!=GetInstigator())
	{
		if(OtherActor->CanBeDamaged() && GetInstigator())
		{
			OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), GetInstigator());
		}
		if(ProjectileImpact)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ProjectileImpact, Hit.ImpactPoint, FRotationMatrix::MakeFromX(Hit.ImpactNormal).Rotator());
		}
		Destroy();
	}
}
