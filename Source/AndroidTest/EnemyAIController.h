#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AITypes.h"
#include "MyCharacter.h"

#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EnemyAIController.generated.h"


UCLASS()
class ANDROIDTEST_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

	AEnemyAIController();
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* PerceptionComp = nullptr;

	UPROPERTY(EditAnywhere)
	UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere)

	UAISenseConfig_Hearing* HearingConfig;
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


	AMyCharacter* FpsCharacter;


	virtual FRotator GetControlRotation() const override;


	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);


	class AEnemy* Enemy;

	void EnemyThrowTheSlipper();
public:
	void ResetBT();
};
