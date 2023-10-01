#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
UCLASS(config = Game)
class ANDROIDTEST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveRight(float Value);
	void MoveForward(float Value);


	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraSpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnlargedObjects{};

public:
	bool bCaught{false};
	UPROPERTY(EditAnywhere)
	bool bCharacterCanJump{true};

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GunMesh;
	UFUNCTION()
	void Jump_2();

	UFUNCTION()
	void OnTouchBegin(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
	void OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location);

	FVector2D InitialTouchLocation;
	bool bIsTouching;

	UPROPERTY(EditAnywhere)
	float CameraRotationSpeed{0.3f};


	void Die();
};
