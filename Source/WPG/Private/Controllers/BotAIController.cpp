// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/BotAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ABotAIController::ABotAIController()
{
	// Blackboard
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	// Run BT if it's valid
	if (BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Init blackboard
	Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
}
