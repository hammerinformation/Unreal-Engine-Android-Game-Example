#include "WeaponComponent.h"
#include "EnemyAIController.h"
#include "FurnitureComponent.h"
#include "MyHUD.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	FpsCharacter = Cast<AMyCharacter>(GetOwner());
	SetComponentTickInterval(0.2f);
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Check();

	if (FireProgress <= 100.0f)
	{
		FireProgress += 0.5f;
	}
	if (FireProgress >= 100.f)
	{
		FireProgress = 100.f;
	}


	{
		return;
		if (FpsCharacter && BP_Enemy)
		{
			const float Height = FpsCharacter->GetActorLocation().Z - BP_Enemy->GetActorLocation().Z;


			const float Distance = FVector::Distance(FpsCharacter->GetActorLocation(),
			                                         BP_Enemy->GetActorLocation());


			GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Black,
			                                 FString::Printf(TEXT("Height: %f  Distance : %f"), Height, Distance));
		}
	}
}

void UWeaponComponent::Check()
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
			FurnitureComponent = Cast<UFurnitureComponent>(
				OutHit.GetActor()->FindComponentByClass<UFurnitureComponent>());
			Enemy = Cast<AEnemy>(OutHit.GetActor());
			if ((Enemy && FVector::Distance(Enemy->GetActorLocation(), FpsCharacter->GetActorLocation()) <
					RaycastDistance) || FurnitureComponent && FVector::Distance(
					FurnitureComponent->GetOwner()->GetActorLocation(),
					FpsCharacter->GetActorLocation()) <
				RaycastDistance)
			{
				return;
			}
		}
		FurnitureComponent = nullptr;
		Enemy = nullptr;
	}
}

void UWeaponComponent::OnFireButtonClicked()
{
	if (FpsCharacter == nullptr || BP_Enemy == nullptr) { return; }
	if (FpsCharacter->GunMesh->IsVisible())
	{
		const float Height = FpsCharacter->GetActorLocation().Z - BP_Enemy->GetActorLocation().Z;
		const float Distance = FVector::Distance(FpsCharacter->GetActorLocation(),
		                                         BP_Enemy->GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Red,
		                                 FString::Printf(TEXT("Height: %f  Distance : %f"), Height, Distance));
		if (Enemy && FireProgress >= 100.f)
		{
			if (Enemy->bIsFrozen == false)

			{
				if (FireSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, FpsCharacter->GetActorLocation());
				}

				FireProgress = 0.0f;
				SpawnParticle(Enemy->GetActorLocation());

				Enemy->StopEnemy();
			}
		}
	}
	if (FpsCharacter->GunMesh->IsVisible())
	{
		if (FurnitureComponent)
		{
			if (FurnitureComponent->bIsFinished) { return; }
			if (FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, FpsCharacter->GetActorLocation());
			}
			FurnitureComponent->bIsFinished = true;

			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald,TEXT("OnFireButtonClicked"));

			if (BP_Enemy)
			{
				if (FpsCharacter->GetController()->LineOfSightTo(BP_Enemy) == false)
				{
					UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetOwner()->GetActorLocation(), 1.0f, GetOwner(),
													   3500.0f);
				}
			}

			FurnitureComponent->GetOwner()->SetActorScale3D(FurnitureComponent->DropScale * 1.5f);
			FurnitureComponent->DropScale = FurnitureComponent->GetOwner()->GetActorScale3D();
			FurnitureComponent->TakeScale = FurnitureComponent->GetOwner()->GetActorScale3D() / 10.0f;
			if (UStaticMeshComponent* MeshComponent = FurnitureComponent->GetOwner()->FindComponentByClass<
				UStaticMeshComponent>())
			{
				MeshComponent->SetSimulatePhysics(true);
				MeshComponent->SetCanEverAffectNavigation(false);
			}
			
			if (FpsCharacter)
			{
				FpsCharacter->EnlargedObjects += 1;
				if (FpsCharacter->EnlargedObjects == 100)
				{
					if (const AMyHUD* const Hud2 = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
					{
						Hud2->MyUserWidget->WinCanvasPanel->SetVisibility(ESlateVisibility::Visible);

						if (BP_Enemy)
						{
							if (AEnemyAIController* const EnemyAIController = Cast<AEnemyAIController>(
								BP_Enemy->GetController()))
							{
								EnemyAIController->GetBlackboardComponent()->SetValueAsBool("PlayerWon", true);
								EnemyAIController->ResetBT();
							}
						}
					}
				}
			}
		}
	}
}

void UWeaponComponent::SpawnParticle(const FVector& Location) const
{
	if (ObjectParticle)
	{
		AActor* const SpawnedParticle = GetWorld()->SpawnActor<AActor>(ObjectParticle, Location, FRotator::ZeroRotator);
		SpawnedParticle->SetLifeSpan(9.5f);
	}
}
