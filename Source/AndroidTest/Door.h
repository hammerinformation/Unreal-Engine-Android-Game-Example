
#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "InteractableObject.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class ANDROIDTEST_API ADoor : public AActor,public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	ADoor();

	
protected:
	virtual void BeginPlay() override;

private:
	bool bIsOpen{};
	bool bPlayAnimation{};

	void Open();
	void Close();
public:	

	virtual void Tick(float DeltaTime) override;


	virtual void Interact() override;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* DoorMesh{};

	UPROPERTY(EditAnywhere)
	AEnemy* Enemy{};





	
};
