// Shooter Games DEV


#include "Components/SWeaponComponent.h"
#include "Weapon/SBaseWeapon.h"
#include "GameFramework/Character.h"

//class ASBaseWeapon;
// Sets default values for this component's properties
USWeaponComponent::USWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	// ...
	
}

// Called every frame
//void USWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

void USWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())return;

	CurentWeapon = GetWorld()->SpawnActor<ASBaseWeapon>(WeaponClass);

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)return;

	if (!CurentWeapon)return;

	//UE_LOG(BaseCharacterLog, Display, TEXT("SpawnWeapon!!!!!!!!!!!!!!"));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	//b_RightWeaponSocket
	CurentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurentWeapon->SetOwner(Character);
	
}

//void USWeaponComponent::Fire()
//{
//	if (!CurentWeapon)return;
//	CurentWeapon->Fire();
//}

void USWeaponComponent::StartFire()
{
	if (!CurentWeapon)return;
	CurentWeapon->StartFire();
}

void USWeaponComponent::StopFire()
{
	if (!CurentWeapon)return;
	CurentWeapon->StopFire();
}