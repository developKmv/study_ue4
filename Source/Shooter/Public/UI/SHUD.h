// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();
};
