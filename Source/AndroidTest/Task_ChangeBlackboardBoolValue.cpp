#include "Task_ChangeBlackboardBoolValue.h"

#include "BehaviorTree/BlackboardComponent.h"


UTask_ChangeBlackboardBoolValue::UTask_ChangeBlackboardBoolValue()
{
	NodeName = "Change Blackboard Bool Value";
}

EBTNodeResult::Type UTask_ChangeBlackboardBoolValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* const BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(TargetKey.SelectedKeyName, NewValue);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
