

#include "Service_ChangeSpeed.h"

#include "Enemy.h"
#include "EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UService_ChangeSpeed::UService_ChangeSpeed()
{
	NodeName="ChangeSpeed";
	bNotifyBecomeRelevant=true;
}

void UService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto const AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemy* const Enemy = Cast<AEnemy>(AIController->GetPawn());
	Enemy->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	Enemy->GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
}
