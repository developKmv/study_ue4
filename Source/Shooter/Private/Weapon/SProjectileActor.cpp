// Shooter Games DEV


#include "Weapon/SProjectileActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ASProjectileActor::ASProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ASProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

