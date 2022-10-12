// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"

#include "Kismet/GameplayStatics.h"


void AShooterGameMode::SendLooseEvent()
{
	OnLoose.Broadcast();
}

void AShooterGameMode::AddScore(int32 Amount)
{
	Score += Amount;
	OnScoreChanged.Broadcast();
}

void AShooterGameMode::Loose_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilationValue);
	GetWorld()->GetTimerManager().SetTimer(TimeToEndGameHandle, this, &AShooterGameMode::SendLooseEvent, EndGameTimer);
}

void AShooterGameMode::Win_Implementation()
{
	OnWin.Broadcast();
}
