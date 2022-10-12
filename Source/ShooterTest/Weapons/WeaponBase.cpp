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

void AWeaponBase::PlayAnimation(UAnimMontage* Animation)
{
	if (Animation)
	{
		if(auto* Player = Cast<APlayerCharacter>(Character))
		{
			UAnimInstance* AnimInstance = Player->GetMesh1P()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(Animation, 1.f);
			}
		}
		else
		{
			UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(Animation, 1.f);
			}
		}
		
	}

}

void AWeaponBase::PlaySound(USoundBase* Sound)
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

FRotator AWeaponBase::CalculateSpread(FVector Direction, float MaxAngle) const
{
	return FRotationMatrix::MakeFromX(FMath::VRandCone(Direction, MaxAngle)).Rotator();
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
	
	if(AttackShake)
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), AttackShake, GetActorLocation(), 0.f, 500.f);
	}

	PlayAnimation(FireAnimation);
	
	PlaySound(FireSound);
	
	bCanAttack = false;
	bCanDoAltAttack = false;
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AWeaponBase::ResetAttack, AttackRate);
	GetWorld()->GetTimerManager().SetTimer(AltAttackTimerHandle, this, &AWeaponBase::ResetAltAttack, AttackRate);

}

void AWeaponBase::AltFire()
{
	if(!bCanDoAltAttack	) return;
	if (AltAttackProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < AltAttackTotalProjectiles; i++)
			{
				const FRotator SpawnRotation = CalculateSpread(Character->GetControlRotation().Vector(), AltFireSpreadExponent);
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr)
					                               ? FP_MuzzleLocation->GetComponentLocation()
					                               : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				ActorSpawnParams.Instigator = Character;
				AShooterTestProjectile* Projectile = World->SpawnActor<AShooterTestProjectile>(
					AltAttackProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				if (!Projectile) return;
				Projectile->Initialize(AltAttackDamage, AltAttackProjectileSpeed);
			}
		}
	}

	if(AltAttackShake)
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), AltAttackShake, GetActorLocation(), 0.f, 500.f);
	}

	PlayAnimation(AltFireAnimation);
	
	PlaySound(AltFireSound);
	
	bCanAttack = false;
	bCanDoAltAttack = false;
	GetWorld()->GetTimerManager().SetTimer(AltAttackTimerHandle, this, &AWeaponBase::ResetAltAttack, AltAttackCooldown);
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AWeaponBase::ResetAttack, AttackRate);
	
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

void AWeaponBase::ResetAltAttack()
{
	bCanDoAltAttack=true;
}
