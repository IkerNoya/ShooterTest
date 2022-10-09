// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERTEST_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	AWeaponBase* FP_Gun;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	APlayerCharacter();
protected:
	virtual void BeginPlay() override;
	virtual void Attack_Implementation() override;
	virtual void AltAttack_Implementation() override;
	virtual void Die_Implementation() override;

public:
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AWeaponBase* GetWeapon() const {return FP_Gun;}
	
};
