// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "ShooterTest/Character/CharacterBase.h"

AEnemyController::AEnemyController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	BrainComponent = CreateDefaultSubobject<UBrainComponent>(TEXT("Brain"));
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	RunBehaviorTree(Behavior);
	if (BrainComponent)
	{
		BrainComponent->StartLogic();
	}
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionUpdate);
	
	Super::OnPossess(InPawn);
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyController::PerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if(auto* Target = Cast<ACharacterBase>(Actor))
	{
		if(Target->IsPlayerControlled())
		{
			Blackboard->SetValueAsObject(TargetKeyName, Target);
		}
	}
}
