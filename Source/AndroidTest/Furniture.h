
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "GameFramework/Actor.h"
#include "Furniture.generated.h"

UCLASS()
class ANDROIDTEST_API AFurniture : public AActor 
{
	GENERATED_BODY()
	
public:	
	AFurniture();

protected:
	virtual void BeginPlay() override;



	
public:	
	virtual void Tick(float DeltaTime) override;

};
