// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneBase.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterTest/Core/GameMode/ShooterGameMode.h"


ADroneBase::ADroneBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ADroneBase::BeginPlay()
{
	Super::BeginPlay();
	if(!HealthComponent) return;

	HealthComponent->OnDeath.AddDynamic(this, &ADroneBase::Die);
}

void ADroneBase::Die_Implementation()
{
	if(auto* GameMode = Cast<AShooterGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AddScore(ScoreToAdd);
	}
}

float ADroneBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                             AActor* DamageCauser)
{
	if(HealthComponent)
	{
		HealthComponent->TakeDamage(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ADroneBase::Attack_Implementation()
{
	if(AttackSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation());
	}
}
