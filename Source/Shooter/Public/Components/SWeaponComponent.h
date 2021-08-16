// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWeaponComponent.generated.h"
//#include "Weapon/SBaseWeapon.h"

class ASBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USWeaponComponent();
	//void SpawnWeapon();
	//void Fire();
	void StartFire();
	void StopFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<ASBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponAttachPointName = "b_RightWeaponSocket";
	
private:	
	UPROPERTY()
		ASBaseWeapon* CurentWeapon = nullptr;

	void SpawnWeapon();
		
};
