
#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_FindRandomLocation.generated.h"


UCLASS()
class ANDROIDTEST_API UTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UTask_FindRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

	UPROPERTY(EditAnywhere)
	TArray<FVector> RandomLocationList{};

	
private:
	AEnemyAIController* EnemyAIController{};
};
