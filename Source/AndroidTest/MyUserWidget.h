
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyUserWidget.generated.h"

UCLASS()
class ANDROIDTEST_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct()override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
		UButton* DoorButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UButton* JumpButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UButton* WeaponButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UProgressBar* FireProgressBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* FrozenText;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* EnlargedObjectsText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UCanvasPanel* FailCanvasPanel;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UCanvasPanel* WinCanvasPanel;
	
UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Example{45.43f};
};
