// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SLauncherBaseWeapon.generated.h"

/**
 * 
 */
class ASProjectileActor;
UCLASS()
class SHOOTER_API ASLauncherBaseWeapon : public ASBaseWeapon
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ASProjectileActor> ProjectileClass;

	virtual void MakeShot() override;
};
