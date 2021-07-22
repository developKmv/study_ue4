// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTER_API ASBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBaseWeapon();
	virtual void Fire();
	void MakeShot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TraceMaxDistance=1500.0f;
};
