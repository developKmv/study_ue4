// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta=(ClampMin="1.5",ClampMax="10.0"))
		float RunModify = 2.0f;


	virtual float GetMaxSpeed() const override;
};
