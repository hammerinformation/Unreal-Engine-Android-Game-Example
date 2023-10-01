#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_EnableMovement.generated.h"


UCLASS()
class ANDROIDTEST_API UTask_EnableMovement : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UTask_EnableMovement();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;


	UPROPERTY(EditAnywhere)
	bool bEnable{false};


private:
	AEnemyAIController* EnemyAIController{};
	AEnemy* EnemyPawn{};
};
