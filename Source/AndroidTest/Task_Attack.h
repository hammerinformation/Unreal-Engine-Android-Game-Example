
#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_Attack.generated.h"

UCLASS()
class ANDROIDTEST_API UTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_Attack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;


	
private:
	AEnemyAIController* EnemyAIController{};
};
