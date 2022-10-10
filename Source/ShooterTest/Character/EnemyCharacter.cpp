// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "ShooterTest/Core/GameMode/ShooterGameMode.h"


void AEnemyCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	if(auto* GameMode = Cast<AShooterGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AddScore(ScoreToAdd);
	}
}

void AEnemyCharacter::Attack_Implementation()
{
	Super::Attack_Implementation();
	if(!bCanAttack) return;
	OnFire.Broadcast();
}
