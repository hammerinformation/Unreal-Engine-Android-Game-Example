#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Slipper.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class ANDROIDTEST_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;


public:

	void ThrowTheSlipper();

	UPROPERTY(EditAnywhere)
	ASlipper* Slipper{};

	UPROPERTY(EditAnywhere)
	AMyCharacter* Player{};

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnimMontage{};

	UPROPERTY(EditAnywhere)
	UAnimMontage* ThrowAnimMontage{};
	void Attack();

	UPROPERTY(VisibleAnywhere)
	bool bThrew = false;


	UPROPERTY(EditAnywhere)
	bool bIsFrozen{false};
	void StopEnemy();
	void StartEnemy();
	AEnemyAIController* EnemyAIController{};
};
