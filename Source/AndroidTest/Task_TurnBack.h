// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_TurnBack.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDTEST_API UTask_TurnBack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UTask_TurnBack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UPROPERTY(EditAnywhere)
	float TimeToWait;
	float ElapsedTime;
};
