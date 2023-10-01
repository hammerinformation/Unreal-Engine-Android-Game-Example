#include "DoorSensor.h"



UDoorSensor::UDoorSensor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDoorSensor::BeginPlay()
{
	Super::BeginPlay();

}


void UDoorSensor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}
