// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "ShooterTest/Components/HealthComponent.h"
#include "DroneBase.generated.h"

UCLASS()
class SHOOTERTEST_API ADroneBase : public APawn
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UFloatingPawnMovement* PawnMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bCanAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 ScoreToAdd = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	USoundBase* AttackSound;
public:
	ADroneBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};
