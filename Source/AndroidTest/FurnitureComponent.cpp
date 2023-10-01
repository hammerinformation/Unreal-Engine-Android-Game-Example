#include "FurnitureComponent.h"

#include "InteractionController.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

UFurnitureComponent::UFurnitureComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFurnitureComponent::BeginPlay()
{
	Super::BeginPlay();
	FpsCharacter = Cast<AMyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass()));
	DropScale = GetOwner()->GetActorScale3D();
	TakeScale = DropScale / 10.f;
}

void UFurnitureComponent::Take()
{
	if (UStaticMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>())
	{
		MeshComponent->SetSimulatePhysics(false);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetOwner()->AttachToComponent(FpsCharacter->Camera, FAttachmentTransformRules::KeepWorldTransform);
		GetOwner()->SetActorRelativeLocation(FVector(34, 0, 0));
		GetOwner()->SetActorScale3D(TakeScale);
		FpsCharacter->GunMesh->SetVisibility(false);
		FpsCharacter->FindComponentByClass<UInteractionController>()->TempFurnitureComponent=this;
		FpsCharacter->FindComponentByClass<UInteractionController>()->bIsFurniture=true;
	}
}

void UFurnitureComponent::Drop()
{
	if (UStaticMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>())
	{
		MeshComponent->SetSimulatePhysics(true);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, false);
		GetOwner()->DetachFromActor(DetachRules);
		GetOwner()->SetActorScale3D(DropScale);
		FpsCharacter->GunMesh->SetVisibility(true);
		FpsCharacter->FindComponentByClass<UInteractionController>()->TempFurnitureComponent=nullptr;
		FpsCharacter->FindComponentByClass<UInteractionController>()->bIsFurniture=false;
	}
}


void UFurnitureComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFurnitureComponent::Interact()
{
	bIsHoldingObject = !bIsHoldingObject;
	if (bIsHoldingObject) { Take(); }
	else { Drop(); }
}
