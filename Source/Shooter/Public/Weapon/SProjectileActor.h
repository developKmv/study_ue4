// Shooter Games DEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileActor.generated.h"

class USphereComponent;

UCLASS()
class SHOOTER_API ASProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	USphereComponent* CollisionComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
