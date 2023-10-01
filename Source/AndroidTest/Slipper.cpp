#include "Slipper.h"

#include "EnemyAIController.h"
#include "MyCharacter.h"
#include "MyHUD.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

ASlipper::ASlipper()
{
	SlipperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	RootComponent = SlipperMesh;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(GetRootComponent());
}

void ASlipper::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASlipper::OnComponentBeginOverlap);
	Trigger->SetGenerateOverlapEvents(false);
}

void ASlipper::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (AMyCharacter* const Player = Cast<AMyCharacter>(OtherActor))
	{
		if (Player->bCaught == false)
		{
			Player->Die();
			if (Enemy)
			{
				if (AEnemyAIController*const  EnemyAIController = Cast<AEnemyAIController>(Enemy->GetController()))
				{
					EnemyAIController->GetBlackboardComponent()->SetValueAsBool("PlayerDied", true);
					EnemyAIController->ResetBT();
				}
			}
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise,TEXT("Player -_-"));
	}
}
