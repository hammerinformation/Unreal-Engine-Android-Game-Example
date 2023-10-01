#include "Enemy.h"

#include "EnemyAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	bThrew = false;
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EnemyAIController = Cast<AEnemyAIController>(GetController());
	if (Slipper)
	{
		Slipper->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHandSocket");
		Slipper->SetActorRelativeLocation(FVector(-0.2f, -0.2f, 0.1f));

		const FRotator RotatorValue(180, 90, 0.0f);
		const FQuat QuatValue = RotatorValue.Quaternion();
		Slipper->SetActorRelativeRotation(QuatValue);
		Slipper->SetActorRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	}
}



void AEnemy::ThrowTheSlipper()
{

	FLatentActionInfo Lt;
	Lt.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(GetRootComponent(),
	                                      GetActorLocation(),
	                                      (Player->GetActorLocation() - GetActorLocation()).Rotation(), false, false,
	                                      0.1f, false,
	                                      EMoveComponentAction::Move, Lt);

	if (UEnemyAnimInstance* const EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (ThrowAnimMontage)
		{
			EnemyAnimInstance->Montage_Play(ThrowAnimMontage, 1.5f);
		}
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		Slipper->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Slipper->SetActorScale3D(FVector::OneVector);
		Slipper->Trigger->SetGenerateOverlapEvents(true);


		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(Slipper->GetRootComponent(),
		                                      Player->GetActorLocation() + FVector::UpVector * 40.f,
		                                      FRotator::ZeroRotator,
		                                      false, false, 0.34f, false,
		                                      EMoveComponentAction::Move, LatentInfo);
		bThrew = true;
	
	}), 0.5f, false);
}




void AEnemy::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald,TEXT(" AEnemy::Attack()"));
	if (UEnemyAnimInstance* const EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (AttackAnimMontage)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald,TEXT("EnemyAnimInstance->Montage_Play"));
			EnemyAnimInstance->Montage_Play(AttackAnimMontage);
		}
	}
}

void AEnemy::StopEnemy()
{
	bIsFrozen = true;
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool("IsFrozen", true);
	GetCharacterMovement()->DisableMovement();

	GetMesh()->bPauseAnims = true;
}

void AEnemy::StartEnemy()
{
	bIsFrozen = false;
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool("IsFrozen", false);

	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	GetMesh()->bPauseAnims = false;
}
