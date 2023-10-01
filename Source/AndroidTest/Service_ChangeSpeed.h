
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Service_ChangeSpeed.generated.h"


UCLASS()
class ANDROIDTEST_API UService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UService_ChangeSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed = 25.0f;
	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 64.0f;

};
