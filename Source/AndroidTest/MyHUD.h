
#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class ANDROIDTEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InteractionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyUserWidget* MyUserWidget;
};
