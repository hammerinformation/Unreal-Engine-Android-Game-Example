#include "MyCharacter.h"
#include "MyHUD.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"


AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComponent->SetRelativeLocation(FVector(0, 0, 60));
	CameraSpringArmComponent->SetupAttachment(GetCapsuleComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraSpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GunMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->AttachToComponent(Camera,FAttachmentTransformRules::KeepRelativeTransform);
}


void AMyCharacter::BeginPlay()
{
	
	Super::BeginPlay();

	bIsTouching = false;
	bCharacterCanJump = true;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyCharacter::MoveRight);
	//PlayerInputComponent->BindAxis("Gamepad_LeftX", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Vertical", this, &AMyCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("Gamepad_LeftX", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("HorizontalRotation", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("VerticalRotation", this, &AMyCharacter::LookUpAtRate);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyCharacter::OnTouchBegin);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AMyCharacter::OnTouchEnd);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyCharacter::OnTouchMove);
}

void AMyCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}


void AMyCharacter::Jump_2()
{
		ACharacter::Jump();

}

void AMyCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate);
}

void AMyCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate);
}

void AMyCharacter::OnTouchBegin(ETouchIndex::Type FingerIndex, FVector Location)
{
	bIsTouching = true;
	InitialTouchLocation = FVector2D(Location);
}

void AMyCharacter::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bIsTouching)
	{
		FVector2D CurrentTouchLocation = FVector2D(Location);
		FVector2D DeltaTouchLocation = CurrentTouchLocation - InitialTouchLocation;
		InitialTouchLocation = CurrentTouchLocation;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController && PlayerController->GetPawn())
		{
			PlayerController->GetPawn()->AddControllerYawInput(DeltaTouchLocation.X * CameraRotationSpeed);
			//USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();

			if (CameraSpringArmComponent)
			{
				float PitchChange = -DeltaTouchLocation.Y * CameraRotationSpeed;
				float NewPitch = FMath::Clamp(CameraSpringArmComponent->GetRelativeRotation().Pitch + PitchChange,
				                              -87.0f, 90.0f);
				CameraSpringArmComponent->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));
			}
		}
	}
}

void AMyCharacter::OnTouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	bIsTouching = false;
}

void AMyCharacter::Die()
{
	if(bCaught){return;}
	bCaught=true;
	GunMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	GunMesh->SetWorldScale3D(FVector::OneVector);
	GunMesh->SetSimulatePhysics(true);
	
	
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(RootComponent, GetActorLocation(), FRotator(180,0,0), false, false, 1.5,
	                                      false, EMoveComponentAction::Move, LatentInfo);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]
	{
		if (const AMyHUD* const My_Hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			My_Hud->MyUserWidget->FailCanvasPanel->SetVisibility(ESlateVisibility::Visible);
		}
	}), 1.25f, false); 


}
