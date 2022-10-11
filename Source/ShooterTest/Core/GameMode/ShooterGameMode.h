// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChanged);
UCLASS()
class SHOOTERTEST_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 Score = 0;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnScoreChanged OnScoreChanged;

public:
	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetScore() const { return Score; }
	
};