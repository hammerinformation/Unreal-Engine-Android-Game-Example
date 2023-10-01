// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_MoveToLastDetectedPlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UTask_MoveToLastDetectedPlayerLocation::UTask_MoveToLastDetectedPlayerLocation()
{
	NodeName = "LastDetectedPlayerLocation";
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UTask_MoveToLastDetectedPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                        uint8* NodeMemory)
{
	

	return EBTNodeResult::InProgress;
}

void UTask_MoveToLastDetectedPlayerLocation::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UTask_MoveToLastDetectedPlayerLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                      float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (EnemyAIController)
	{
		const FVector Target = EnemyAIController->GetBlackboardComponent()->GetValueAsVector("LastSeenPlayerLocation");
		EnemyAIController->MoveToLocation(Target);

		if (FVector::Distance(EnemyAIController->GetPawn()->GetActorLocation(), Target) < Distance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
