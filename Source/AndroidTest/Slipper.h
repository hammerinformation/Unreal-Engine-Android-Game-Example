// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Slipper.generated.h"
class AEnemy;
UCLASS()
class ANDROIDTEST_API ASlipper : public AActor
{
	GENERATED_BODY()
	
public:	
	ASlipper();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	AEnemy* Enemy{};
	
	UPROPERTY(EditAnywhere)
	 UBoxComponent* Trigger{};
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SlipperMesh{};



	UFUNCTION()
			void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
				AActor* OtherActor,
				UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex,
				bool bFromSweep,
				const FHitResult& SweepResult);


};
