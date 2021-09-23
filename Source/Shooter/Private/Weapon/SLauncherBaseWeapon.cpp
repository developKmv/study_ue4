// Shooter Games DEV


#include "Weapon/SLauncherBaseWeapon.h"
#include "Weapon/SProjectileActor.h"
#include "Kismet/GameplayStatics.h"
void ASLauncherBaseWeapon::StartFire()
{
	MakeShot();
}

void ASLauncherBaseWeapon::MakeShot()
{
	const FTransform SpawnTransform(FRotator::ZeroRotator,GetMuzzleWorldLocation());
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	//set projectile params
	UGameplayStatics::FinishSpawningActor(Projectile,SpawnTransform);
}