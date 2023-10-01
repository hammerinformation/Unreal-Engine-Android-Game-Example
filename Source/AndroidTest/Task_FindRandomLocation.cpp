

#include "Task_FindRandomLocation.h"

#include "BehaviorTree/BlackboardComponent.h"


UTask_FindRandomLocation::UTask_FindRandomLocation()
{
	NodeName="FindRandomLocation";
	bCreateNodeInstance=true;
	
}
EBTNodeResult::Type UTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if(EnemyAIController)
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsVector("RandomLocation",RandomLocationList[FMath::RandRange(0,RandomLocationList.Num()-1)]);
		return  EBTNodeResult::Succeeded;
	}
	return  EBTNodeResult::Failed;

}

void UTask_FindRandomLocation::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);

	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
}
