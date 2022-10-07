// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthComponent::Death_Implementation()
{
	bIsDead = true;
	OnDeath.Broadcast();
}

void UHealthComponent::TakeDamage(float Damage)
{
	if(bIsDead) return;
	
	float OldValue = CurrentHealth;
	CurrentHealth -= Damage;
	if(CurrentHealth <= 0)
	{
		Death();
		return;
	}
	OnDamageTaken.Broadcast(OldValue, CurrentHealth);
}

void UHealthComponent::Heal(float Amount)
{
	if(bIsDead) return;
	
	float OldValue = CurrentHealth;
	float NewValue = CurrentHealth + Amount;
	if(CurrentHealth >= MaxHealth) return;

	CurrentHealth = NewValue >= MaxHealth ? MaxHealth : NewValue;
	
	OnHeal.Broadcast(OldValue, CurrentHealth);
}


