// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_MoveToLastDetectedPlayerLocation.generated.h"


UCLASS()
class ANDROIDTEST_API UTask_MoveToLastDetectedPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_MoveToLastDetectedPlayerLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;

	UPROPERTY(EditAnywhere)
	float Distance{150.f};
	
	AMyCharacter* Player;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	AEnemyAIController* EnemyAIController{};
};
