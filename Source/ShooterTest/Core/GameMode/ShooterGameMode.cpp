// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"

#include "Kismet/GameplayStatics.h"


void AShooterGameMode::SendLooseEvent()
{
	OnLoose.Broadcast();
}

void AShooterGameMode::SendWinEvent()
{
	OnWin.Broadcast();
}

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), Enemies);
}

void AShooterGameMode::AddScore(int32 Amount)
{
	Score += Amount;
	OnScoreChanged.Broadcast();
}

void AShooterGameMode::RemoveEnemyFromArray(AActor* Enemy)
{
	if(Enemy && Enemies.Num() > 0 && Enemies.Contains(Enemy))
	{
		Enemies.Remove(Enemy);
	}
	if(Enemies.Num() <= 0)
	{
		Win();
	} 
}

void AShooterGameMode::Loose_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilationValue);
	GetWorld()->GetTimerManager().SetTimer(TimeToEndGameHandle, this, &AShooterGameMode::SendLooseEvent, EndGameTimer);
}

void AShooterGameMode::Win_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilationValue);
	GetWorld()->GetTimerManager().SetTimer(TimeToEndGameHandle, this, &AShooterGameMode::SendWinEvent, EndGameTimer);
}
