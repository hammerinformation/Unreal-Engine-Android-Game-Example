#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TakeAndDrop.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROIDTEST_API UTakeAndDrop : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTakeAndDrop();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	class UDoorSensor* DoorSensor;


	UPROPERTY(EditAnywhere)
	class AMyCharacter* FpsCharacter{};

};
