#include "EnemyAIController.h"


#include "Engine/Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Enemy.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*PerceptionComp);
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	FpsCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Enemy = Cast<AEnemy>(GetPawn());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.
	                          AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
	ReceiveMoveCompleted.AddDynamic(this, &AEnemyAIController::OnMoveCompleted);

}


void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == FpsCharacter && Stimulus.WasSuccessfullySensed() && GetBlackboardComponent() &&
		GetBlackboardComponent()->GetValueAsBool("PlayerDied") == false)
	{
		GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", true);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", false);
	}
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
	                                 FString::Printf(TEXT("EPathFollowingResult::Type: %d"), Result));
	if (Enemy && Enemy->bThrew)
	{
		return;
	}

	if (Result == EPathFollowingResult::Invalid)
	{
		
		GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", false);
		ResetBT();
	}
	if (Result == EPathFollowingResult::Success)
	{
		const float Dis = FpsCharacter->GetDistanceTo(GetPawn());
		if (Dis < 650.f)
		{
			EnemyThrowTheSlipper();


			return;
		}

	////////////////////////////////////////////////
	GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", false);
	GetPerceptionComponent()->Deactivate();
	ResetBT();
	FRotator Rot = GetPawn()->GetActorRotation();
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	Rot.Yaw += 180;
	UKismetSystemLibrary::MoveComponentTo(GetPawn()->GetRootComponent(), GetPawn()->GetActorLocation(),
	                                      FRotator(Rot), false, false, 0.5f, false,
	                                      EMoveComponentAction::Move, LatentInfo);

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		GetPerceptionComponent()->Activate();
	}), 1.5f, false);


	}

}


void AEnemyAIController::EnemyThrowTheSlipper()
{
	if (Enemy && FpsCharacter && LineOfSightTo(FpsCharacter))
	{
		if (GetBlackboardComponent())
		{
			if (UBehaviorTreeComponent* const BehaviorTreeComp = Cast<UBehaviorTreeComponent>(BrainComponent))
			{
				BehaviorTreeComp->PauseLogic("Example");
			}
		}


		GetPerceptionComponent()->Deactivate();
		GetBlackboardComponent()->SetValueAsBool("HasLineOfSight", false);
		FpsCharacter->FindComponentByClass<UCharacterMovementComponent>()->DisableMovement();
		Enemy->ThrowTheSlipper();
	}
}

void AEnemyAIController::ResetBT()
{
	if (GetBlackboardComponent())
	{
		if (UBehaviorTreeComponent* const BehaviorTreeComp = Cast<UBehaviorTreeComponent>(BrainComponent))
		{
			BehaviorTreeComp->RestartTree();
		}
	}
}


FRotator AEnemyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator();
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetBlackboardComponent() && GetBlackboardComponent()->GetValueAsBool("HasLineOfSight"))
	{
		GetBlackboardComponent()->SetValueAsVector("LastSeenPlayerLocation", FpsCharacter->GetActorLocation());
		GetBlackboardComponent()->SetValueAsFloat(
			"Distance", FVector::Distance(GetPawn()->GetActorLocation(), FpsCharacter->GetActorLocation()));
	}
}
