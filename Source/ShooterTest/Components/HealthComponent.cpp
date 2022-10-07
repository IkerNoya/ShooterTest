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
	OnDeath.Broadcast();
}

void UHealthComponent::TakeDamage(float Damage)
{
	CurrentHealth -= Damage;
}

void UHealthComponent::Heal(float Amount)
{
	CurrentHealth += Amount;
}


