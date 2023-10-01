
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyAIController.h"
#include "Task_EnableAiPerception.generated.h"


UCLASS()
class ANDROIDTEST_API UTask_EnableAiPerception : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UTask_EnableAiPerception();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

	UPROPERTY(EditAnywhere)
	bool bValue;

	AEnemyAIController* EnemyAIController;
	
};
