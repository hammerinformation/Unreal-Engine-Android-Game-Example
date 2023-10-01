

#include "MyHUD.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();


	if (InteractionWidget)
	{
		MyUserWidget = CreateWidget<UMyUserWidget>(GetWorld(), InteractionWidget);

		if (MyUserWidget)
		{
			MyUserWidget->AddToViewport(-1);
		}
	}
}
