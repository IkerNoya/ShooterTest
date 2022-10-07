// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, OldValue, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class SHOOTERTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	float CurrentHealth = 0.f;
private:
	bool bIsDead = false;
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHealthChanged OnDamageTaken;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHealthChanged OnHeal;
		
	UHealthComponent();
		
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Death();

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float Amount);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	FORCEINLINE float GetHealth() const { return CurrentHealth; }
};
