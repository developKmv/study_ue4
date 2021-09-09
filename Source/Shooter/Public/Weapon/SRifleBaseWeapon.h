// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SRifleBaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASRifleBaseWeapon : public ASBaseWeapon
{
	GENERATED_BODY()


public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TimeBetweenShots = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float BulletSpread = 1.5f;


private:
	FTimerHandle ShotTimerHandle;

};
