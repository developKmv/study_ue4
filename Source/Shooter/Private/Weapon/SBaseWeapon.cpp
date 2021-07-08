// Shooter Games DEV


#include "Weapon/SBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

ASBaseWeapon::ASBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBaseWeapon::Fire()
{
	UE_LOG(BaseWeaponLog, Display, TEXT("Piu Piu"));
}



