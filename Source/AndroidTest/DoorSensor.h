
#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "Components/ActorComponent.h"
#include "DoorSensor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROIDTEST_API UDoorSensor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorSensor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
