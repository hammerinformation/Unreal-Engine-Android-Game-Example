#include "InteractionController.h"

#include "InteractableObject.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyHUD.h"
#include "WeaponComponent.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"

static AMyHUD* MyHud = nullptr;
static UButton* DoorButton = nullptr;
static UButton* JumpButton = nullptr;
static UButton* WeaponButton = nullptr;
static UProgressBar* FireProgressBar = nullptr;
static UWeaponComponent* WeaponComponent_ = nullptr;
static bool bInitialized = false;

UInteractionController::UInteractionController()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInteractionController::Init()
{
	MyHud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (MyHud == nullptr || MyHud->MyUserWidget == nullptr || MyHud->MyUserWidget->DoorButton == nullptr || MyHud->
		MyUserWidget->JumpButton == nullptr || MyHud->MyUserWidget->WeaponButton == nullptr || MyHud->MyUserWidget->
		FireProgressBar == nullptr)
	{
		return;
	}

	DoorButton = MyHud->MyUserWidget->DoorButton;
	JumpButton = MyHud->MyUserWidget->JumpButton;
	WeaponButton = MyHud->MyUserWidget->WeaponButton;
	FireProgressBar = MyHud->MyUserWidget->FireProgressBar;
	JumpButton->OnClicked.AddDynamic(FpsCharacter, &AMyCharacter::Jump_2);
	DoorButton->OnClicked.AddDynamic(this, &UInteractionController::OnClickButtonClicked);

	if (WeaponButton)
	{
		UE_LOG(LogTemp, Log, TEXT("WeaponButton Var"))
	}
	if (JumpButton)
	{
		UE_LOG(LogTemp, Log, TEXT("JumpButton Var"))
	}
	if (FireProgressBar)
	{
		UE_LOG(LogTemp, Log, TEXT("FireProgressBar Var"))
	}
	if (DoorButton)
	{
		UE_LOG(LogTemp, Log, TEXT("DoorButton Var"))
	}
	if (WeaponButton == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("WeaponButton Yok"))
	}
	if (UWeaponComponent* const WeaponComponent = FpsCharacter->FindComponentByClass<UWeaponComponent>())
	{
		WeaponComponent_ = WeaponComponent;
		UE_LOG(LogTemp, Log, TEXT("WeaponComponent Var"))

		if (WeaponButton)
			WeaponButton->OnClicked.AddDynamic(WeaponComponent, &UWeaponComponent::OnFireButtonClicked);
	}

	bInitialized = true;
	SetComponentTickEnabled(true);
	SetComponentTickInterval(0.2f);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("UInteractionController::Init()"));
}

void UInteractionController::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);

	FurnitureComponent = nullptr;
	Door = nullptr;
	bIsFurniture = false;
	FpsCharacter = Cast<AMyCharacter>(GetOwner());
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		Init();
	}), 2.5f, false);
}


void UInteractionController::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bInitialized == false) { return; }


	if (DoorButton != nullptr)
	{
		const bool b = Door || TempFurnitureComponent || FurnitureComponent;
		DoorButton->SetIsEnabled(b);
	}

	if (WeaponComponent_ != nullptr && WeaponButton != nullptr && FireProgressBar != nullptr)
	{
		FireProgressBar->SetPercent(WeaponComponent_->FireProgress / 100.f);
		const bool b = (WeaponComponent_->FurnitureComponent && WeaponComponent_->FurnitureComponent->bIsFinished ==
			false) || (WeaponComponent_->Enemy && FireProgressBar->GetPercent()
			== 1.0f);
		WeaponButton->SetIsEnabled(b);
	}
	CheckInteractableObject();
}

void UInteractionController::CheckInteractableObject()
{
	if (GetWorld() == nullptr) { return; }
	if (APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		FHitResult OutHit;
		FVector Start = PlayerCameraManager->GetCameraLocation();
		FVector ForwardVector = PlayerCameraManager->GetCameraLocation().ForwardVector.GetSafeNormal();
		ForwardVector = PlayerCameraManager->GetCameraRotation().Vector();
		FVector End = ((ForwardVector * RaycastDistance) + Start);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Camera, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				if (ADoor* Temp = Cast<ADoor>(OutHit.GetActor()))
				{
					Door = Temp;
					return;
				}

				if (UFurnitureComponent* Temp1 = Cast<UFurnitureComponent>(
					OutHit.GetActor()->FindComponentByClass<UFurnitureComponent>()))
				{
					if (TempFurnitureComponent == nullptr)
					{
						FurnitureComponent = Temp1;
						return;
					}
				}


				FurnitureComponent = nullptr;
				InteractableObject = nullptr;
				Door = nullptr;
				return;
			}
		}
		InteractableObject = nullptr;
		FurnitureComponent = nullptr;
		Door = nullptr;
	}
}

void UInteractionController::OnClickButtonClicked()
{
	if (Door)
	{
		Door->Interact();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Door->Interact"));

		return;
	}
	if (FurnitureComponent)
	{
		TempFurnitureComponent = FurnitureComponent;
	}
	if (TempFurnitureComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TempFurnitureComponent->Interact"));

		TempFurnitureComponent->Interact();
	}
}
