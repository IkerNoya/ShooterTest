// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SHOOTERTEST_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 ScoreToAdd = 20.f;

	virtual void Die_Implementation() override;
};
