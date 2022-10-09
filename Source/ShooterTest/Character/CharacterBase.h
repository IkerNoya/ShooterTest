// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterTest/Components/HealthComponent.h"
#include "CharacterBase.generated.h"

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
class ACharacterBase : public ACharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bCanAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnFire OnFire;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAltFire OnAltFire;
	
	ACharacterBase();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	


protected:
	
	void Fire();

	void AltFire();
	
	void MoveForward(float Val);
	
	void MoveRight(float Val);
	
	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Die();
	
public:
	
	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AltAttack();
};

