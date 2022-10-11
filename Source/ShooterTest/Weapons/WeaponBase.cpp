// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"
#include "ShooterTest/ShooterTestProjectile.h"
#include "ShooterTest/Character/CharacterBase.h"
#include "ShooterTest/Character/PlayerCharacter.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(Mesh);
	
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(Mesh);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::Fire()
{
	if(!bCanAttack) return;

	OnWeaponFire.Broadcast();
	
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = Character->GetControlRotation();
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr)
				                               ? FP_MuzzleLocation->GetComponentLocation()
				                               : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.Instigator = Character;
			AShooterTestProjectile* Projectile = World->SpawnActor<AShooterTestProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if(!Projectile) return;
			Projectile->Initialize(Damage, ProjectileSpeed);
		}
	}
	if (FireAnimation != nullptr)
	{
		if(auto* Player = Cast<APlayerCharacter>(Character))
		{
			UAnimInstance* AnimInstance = Player->GetMesh1P()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
		else
		{
			UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
		
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	bCanAttack = false;
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AWeaponBase::ResetAttack, AttackRate);
}

void AWeaponBase::AltFire()
{
}

void AWeaponBase::SetUser(ACharacterBase* User)
{
	Character = User;
	if(Character)
	{
		Character->OnFire.AddDynamic(this, &AWeaponBase::Fire);
		Character->OnAltFire.AddDynamic(this, &AWeaponBase::AltFire);
	}
}

void AWeaponBase::ResetAttack()
{
	bCanAttack = true;
}
