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
	bool GetPlayerViewPoint(FVector& ViewLocation,FRotator& ViewRotation) const;
	bool GetTraceData(FVector& TraceStart,FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);
	void MakeDamage(const FHitResult& HitResult);

	FVector GetMuzzleWorldLocation() const;
	APlayerController* GetPlayerController() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TraceMaxDistance=1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DamageAmount = 10.0f;
};
