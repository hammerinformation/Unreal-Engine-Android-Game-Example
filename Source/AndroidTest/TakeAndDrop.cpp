

#include "TakeAndDrop.h"
#include "DoorSensor.h"
#include "MyCharacter.h"


UTakeAndDrop::UTakeAndDrop()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTakeAndDrop::BeginPlay()
{
	Super::BeginPlay();

	DoorSensor=GetOwner()->FindComponentByClass<UDoorSensor>();
	FpsCharacter = Cast<AMyCharacter>(GetOwner());

	
}


void UTakeAndDrop::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

