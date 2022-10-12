// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterTest/Character/CharacterBase.h"
#include "ShooterTest/Character/CharacterBase.h"
#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFire);
UCLASS()
class SHOOTERTEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	ACharacterBase* Character;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* FP_MuzzleLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Weapon|Settings")
	TSubclassOf<class AShooterTestProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Weapon|Settings")
	TSubclassOf<class AShooterTestProjectile> AltAttackProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Settings")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Settings")
	USoundBase* AltFireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	UAnimMontage* AltFireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Settings")
	FVector GunOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|AltAttack")
	float AltAttackDamage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack")
	float ProjectileSpeed = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|AltAttack")
	float AltAttackProjectileSpeed = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack")
	float AttackRate = .25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|AltAttack")
	float AltAttackCooldown = .5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|AltAttack")
	int32 AltAttackTotalProjectiles = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|AltAttack", meta=(ClampMin = 0.0, ClampMax = 0.25))
	float AltFireSpreadExponent = .1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack")
	TSubclassOf<UCameraShakeBase> AttackShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|AltAttack")
	TSubclassOf<UCameraShakeBase> AltAttackShake;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bCanAttack = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bCanDoAltAttack = true;

private:
	FTimerHandle AttackTimerHandle;
	FTimerHandle AltAttackTimerHandle;
		
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeaponFire OnWeaponFire;
	
	AWeaponBase();

private:
	void PlayAnimation(UAnimMontage* Animation);
	void PlaySound(USoundBase* Sound);
	FRotator CalculateSpread(FVector Direction, float MaxAngle) const;
	
protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void Fire();
	UFUNCTION()
	void AltFire();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetUser(ACharacterBase* User);

	UFUNCTION()
	void ResetAttack();
	UFUNCTION()
	void ResetAltAttack();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetDamage() const {return Damage;} 
	UFUNCTION(BlueprintCallable)
	void SetDamage(float Value) { Damage = Value; }
};
