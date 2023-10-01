#include "EnemyAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (TryGetPawnOwner())
	{
		if (const UCharacterMovementComponent* const CharacterMovementComponent = TryGetPawnOwner()->FindComponentByClass<
			UCharacterMovementComponent>())
		{
			Speed = CharacterMovementComponent->MaxWalkSpeed;
		}
		//Speed = TryGetPawnOwner()->GetVelocity().Size();

		//AMyCharacter* Zombie = Cast<AMyCharacter>(TryGetPawnOwner());
	}
}
