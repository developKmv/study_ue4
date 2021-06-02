// Shooter Games DEV


#include "Components/SCharacterMovementComponent.h"
#include "Player/SBaseCharacter.h"

float USCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASBaseCharacter* Player = Cast<ASBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModify : MaxSpeed;
}