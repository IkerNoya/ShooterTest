// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);
UCLASS()
class SHOOTERTEST_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TArray<AActor*> Enemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 Score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float EndGameTimer = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float TimeDilationValue = .5f;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnScoreChanged OnScoreChanged;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameEnd OnLoose;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameEnd OnWin;

private:
	FTimerHandle TimeToEndGameHandle;

	UFUNCTION()
	void SendLooseEvent();
	UFUNCTION()
	void SendWinEvent();

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable)
	void RemoveEnemyFromArray(AActor* Enemy);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetScore() const { return Score; }
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Win();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Loose();
};
