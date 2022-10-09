// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERTEST_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* Behavior;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName TargetKeyName = "Target";

public:
	AEnemyController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	UFUNCTION()
	void PerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
};
