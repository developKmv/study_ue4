// Shooter Games DEV


#include "Weapon/SBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
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
	check(WeaponMesh)
}

//void ASBaseWeapon::Fire()
//{
//	UE_LOG(BaseWeaponLog, Display, TEXT("Piu Piu"));
//	MakeShot();
//}

void ASBaseWeapon::StartFire(){}

void ASBaseWeapon::StopFire() {}

void ASBaseWeapon::MakeShot() {}

APlayerController* ASBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ASBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	//const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void ASBaseWeapon::MakeHit(FHitResult& HitResult,FVector& TraceStart,FVector& TraceEnd)
{
	if(!GetWorld())return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor)return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}