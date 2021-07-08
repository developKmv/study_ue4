// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Components/SHealthComponent.h"
#include "SBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USHealthComponent;
class UTextRenderComponent;
class USWeaponComponent;

UCLASS()
class SHOOTER_API ASBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(900.0f,1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;
	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

private:
	bool WantsToRuns = false;
	bool IsMovingFarward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();
	void OnDeath();
	void OnHealthChanged(float Health);

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

};
