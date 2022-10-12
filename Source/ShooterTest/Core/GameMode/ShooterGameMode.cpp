// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"


void AShooterGameMode::AddScore(int32 Amount)
{
	Score += Amount;
	OnScoreChanged.Broadcast();
}

void AShooterGameMode::Loose_Implementation()
{
	OnLoose.Broadcast();
}

void AShooterGameMode::Win_Implementation()
{
	OnWin.Broadcast();
}
