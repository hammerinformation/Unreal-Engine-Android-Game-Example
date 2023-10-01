// Fill out your copyright notice in the Description page of Project Settings.


#include "SlipperAnimNotifyState.h"

#include "Enemy.h"
#include "Slipper.h"

void USlipperAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (const AEnemy* const Enemy = Cast<AEnemy>(MeshComp->GetOwner()))
	{
		if (Enemy->Slipper)
		{
			Enemy->Slipper->Trigger->SetGenerateOverlapEvents(true);
		}
	}
}

void USlipperAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (const AEnemy* const Enemy = Cast<AEnemy>(MeshComp->GetOwner()))
	{
		if (Enemy->Slipper)
		{
			Enemy->Slipper->Trigger->SetGenerateOverlapEvents(false);
		}
	}
}
