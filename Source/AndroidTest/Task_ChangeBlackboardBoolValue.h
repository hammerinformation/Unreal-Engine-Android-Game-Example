
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_ChangeBlackboardBoolValue.generated.h"



UCLASS()
class ANDROIDTEST_API UTask_ChangeBlackboardBoolValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UTask_ChangeBlackboardBoolValue();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool NewValue;	

};


