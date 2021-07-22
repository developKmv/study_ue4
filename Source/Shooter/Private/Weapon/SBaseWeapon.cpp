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

void ASBaseWeapon::Fire()
{
	UE_LOG(BaseWeaponLog, Display, TEXT("Piu Piu"));
	MakeShot();
}

void ASBaseWeapon::MakeShot()
{
	if(!GetWorld()) return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)return;
	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller)return;
	FVector ViewLocation;
	FRotator ViewRotation;
		
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	/*const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();*/
	const FVector TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	//DrawDebugLine(GetWorld(),TraceStart,TraceEnd,FColor::Red,false,3.0f,0,3.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,24,FColor::Red,false,5.0f);
		UE_LOG(BaseWeaponLog, Display, TEXT("Bone: %s"),*HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}

}

