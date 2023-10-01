

#include "Task_TurnBack.h"
#include "Kismet/KismetSystemLibrary.h"

#include "AIController.h"

UTask_TurnBack::UTask_TurnBack()
{
	NodeName = "Turn Back";
	bNotifyTick = true;
}

EBTNodeResult::Type UTask_TurnBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ElapsedTime = 0.f;
	const auto Enemy = OwnerComp.GetAIOwner()->GetPawn();
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}
	FRotator Rot = Enemy->GetActorRotation();
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	Rot.Yaw+=180;
	UKismetSystemLibrary::MoveComponentTo(Enemy->GetRootComponent(), Enemy->GetActorLocation(),
	                                      FRotator(Rot), false, false, TimeToWait, false,
	                                      EMoveComponentAction::Move, LatentInfo);
	return EBTNodeResult::InProgress;
}

void UTask_TurnBack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	ElapsedTime += DeltaSeconds;

	if (ElapsedTime >= TimeToWait)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
