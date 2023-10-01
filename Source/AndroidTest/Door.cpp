#include "Door.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;
}


void ADoor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickInterval(0.2f);
}

void ADoor::Open()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	auto Rot = GetRootComponent()->GetRelativeRotation() + FRotator(0, 120, 0);
	UKismetSystemLibrary::MoveComponentTo(RootComponent, GetRootComponent()->GetComponentLocation(), Rot,
	                                      false, false, 0.34f, false, EMoveComponentAction::Move, LatentInfo);
}

void ADoor::Close()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	auto Rot = GetRootComponent()->GetRelativeRotation() + FRotator(0, -120, 0);

	UKismetSystemLibrary::MoveComponentTo(RootComponent, GetRootComponent()->GetComponentLocation(),
	                                      Rot, false, false, 0.34f, false, EMoveComponentAction::Move,
	                                      LatentInfo);
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Enemy)
	{
		const float Distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (Distance < 300.f && bIsOpen == false && bPlayAnimation == false)
		{
			bIsOpen = true;
			Open();
		}
	}
}

void ADoor::Interact()
{
	if (bPlayAnimation) { return; }
	bIsOpen = !bIsOpen;
	bPlayAnimation = true;

	DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (bIsOpen) { Open(); }
	else { Close(); }
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		bPlayAnimation = false;
		DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}), 0.40f, false);
}
