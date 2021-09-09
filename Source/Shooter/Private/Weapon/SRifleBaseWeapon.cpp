// Shooter Games DEV


#include "Weapon/SRifleBaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ASRifleBaseWeapon::StartFire()
{
	//UE_LOG(BaseWeaponLog, Display, TEXT("Piu Piu"));
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASRifleBaseWeapon::MakeShot, TimeBetweenShots, true);
}

void ASRifleBaseWeapon::StopFire()
{
	//UE_LOG(BaseWeaponLog, Display, TEXT("Piu Piu"));
	//MakeShot();
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASRifleBaseWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))return;

	/*FVector ViewLocation;
	FRotator ViewRotation;
	GetPlayerViewPoint(ViewLocation, ViewRotation);*/

	//const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	/*const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();*/
	/*const FVector TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;*/

	//DrawDebugLine(GetWorld(),TraceStart,TraceEnd,FColor::Red,false,3.0f,0,3.0f);

	/*FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility, CollisionParams);*/

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		//UE_LOG(BaseWeaponLog, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}

bool ASRifleBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}