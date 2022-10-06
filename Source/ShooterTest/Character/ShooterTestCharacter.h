// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterTestCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class AWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAltFire);

UCLASS(config=Game)
class AShooterTestCharacter : public ACharacter
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
	UPROPERTY(BlueprintAssignable)
	FOnFire OnFire;
	UPROPERTY(BlueprintAssignable)
	FOnAltFire OnAltFire;
	
	AShooterTestCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

protected:
	
	void Fire();

	void AltFire();
	
	void MoveForward(float Val);
	
	void MoveRight(float Val);
	
	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

