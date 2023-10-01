
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Components/ActorComponent.h"
#include "FurnitureComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROIDTEST_API UFurnitureComponent : public UActorComponent,public  IInteractableObject
{
	GENERATED_BODY()

public:	
	UFurnitureComponent();

protected:
	virtual void BeginPlay() override;


private:
	void Take();
	
	void Drop();
	

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	bool bIsHoldingObject{false};
	UPROPERTY(EditAnywhere)
	class AMyCharacter* FpsCharacter{};
	UPROPERTY(EditAnywhere)
	FVector TakeScale{};
	UPROPERTY(EditAnywhere)
	FVector DropScale{};
	virtual void Interact() override;


	bool bIsFinished;
};
