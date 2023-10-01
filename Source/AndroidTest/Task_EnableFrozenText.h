// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_EnableFrozenText.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDTEST_API UTask_EnableFrozenText : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UTask_EnableFrozenText();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:
	UPROPERTY(EditAnywhere)
	bool bEnable{false};
};
