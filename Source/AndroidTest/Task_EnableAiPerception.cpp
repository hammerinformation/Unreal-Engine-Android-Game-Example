#include "Task_EnableAiPerception.h"

UTask_EnableAiPerception::UTask_EnableAiPerception()
{
	NodeName = "Enable Ai Perception";
	bCreateNodeInstance = true;
}

void UTask_EnableAiPerception::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
}

EBTNodeResult::Type UTask_EnableAiPerception::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (EnemyAIController)
	{
		if (bValue)
		{
			EnemyAIController->GetPerceptionComponent()->Activate();
		}
		else
		{
			EnemyAIController->GetPerceptionComponent()->Deactivate();
		}
	}
	return EBTNodeResult::Succeeded;
}
