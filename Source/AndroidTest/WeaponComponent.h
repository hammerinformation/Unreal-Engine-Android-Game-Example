
#pragma once


#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Enemy.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROIDTEST_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	AEnemy* Enemy;

	UPROPERTY(EditAnywhere)
	AEnemy* BP_Enemy;
	UPROPERTY(EditAnywhere)
	class UFurnitureComponent* FurnitureComponent{};
	
	
	void Check();
	UPROPERTY(EditAnywhere)
	float RaycastDistance{500.0f};
	AMyCharacter* FpsCharacter{};

	UFUNCTION()
	void OnFireButtonClicked();

	UPROPERTY(EditAnywhere)
	float FireProgress{0.0f};


	UPROPERTY(EditAnywhere)
	USoundBase* FireSound{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObjectParticle{};
private:
	void SpawnParticle(const FVector& Location) const;
};
