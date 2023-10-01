#include "Task_EnableFrozenText.h"
#include "MyHUD.h"
#include "Components/TextBlock.h"


UTask_EnableFrozenText::UTask_EnableFrozenText()
{
	NodeName = "EnableOrDisableFrozenText";
}

EBTNodeResult::Type UTask_EnableFrozenText::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AMyHUD* const Hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		if (bEnable)
		{
			Hud->MyUserWidget->FrozenText->SetText(FText::FromString(TEXT("ENEMY IS FROZEN FOR 10 SEC")));

		}
		if(bEnable==false)
		{
			Hud->MyUserWidget->FrozenText->SetText(FText::FromString(TEXT(" ")));
		}
	}
	return EBTNodeResult::Succeeded;
}
