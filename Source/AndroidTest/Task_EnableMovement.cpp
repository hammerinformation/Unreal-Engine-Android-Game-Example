#include "Task_EnableMovement.h"

UTask_EnableMovement::UTask_EnableMovement()
{
	NodeName = "EnableMovement";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UTask_EnableMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (EnemyAIController && EnemyPawn)
	{
		if (bEnable)
		{
			EnemyPawn->StartEnemy();
		}
		if (bEnable == false
		)
		{
			EnemyPawn->StopEnemy();
		}


		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UTask_EnableMovement::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	EnemyPawn = Cast<AEnemy>(EnemyAIController->GetPawn());
}
