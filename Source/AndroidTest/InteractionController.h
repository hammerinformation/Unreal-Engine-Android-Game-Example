
#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "FurnitureComponent.h"
#include "Components/ActorComponent.h"
#include "InteractionController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROIDTEST_API UInteractionController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class IInteractableObject* InteractableObject;


	void CheckInteractableObject();
	void Init();
	
	UFUNCTION()
	void OnClickButtonClicked();

	UPROPERTY(EditAnywhere)
	float RaycastDistance{300.0f};

	UPROPERTY(EditAnywhere)
	class AMyCharacter* FpsCharacter{};

	UPROPERTY(EditAnywhere)
	bool bIsFurniture{false};


	UPROPERTY(EditAnywhere)
	 ADoor* Door{};

	UPROPERTY(EditAnywhere)
	 UFurnitureComponent* FurnitureComponent{};

	
	UPROPERTY(EditAnywhere)
	UFurnitureComponent* TempFurnitureComponent{};
	
		
};
