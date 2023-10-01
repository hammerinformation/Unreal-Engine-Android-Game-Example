// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Attack.h"


#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"


UTask_Attack::UTask_Attack()
{
	NodeName = "AttackTask";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (EnemyAIController)
	{
		if (AEnemy* const Enemy = Cast<AEnemy>(EnemyAIController->GetPawn()))
		{
			Enemy->Attack();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

void UTask_Attack::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);

	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
}
