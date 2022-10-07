// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterTest/Character/CharacterBase.h"
#include "ShooterTest/Character/CharacterBase.h"
#include "WeaponBase.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Settings")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
	FVector GunOffset;
		
public:
	AWeaponBase();
	
protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetUser(ACharacterBase* User);
};
