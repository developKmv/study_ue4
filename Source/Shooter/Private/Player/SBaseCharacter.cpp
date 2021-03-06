// Shooter Games DEV


#include "Player/SBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SCharacterMovementComponent.h"
#include "Components/SHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog,All,All);

// Sets default values
ASBaseCharacter::ASBaseCharacter(const FObjectInitializer& ObjInit): Super(ObjInit.SetDefaultSubobjectClass<USCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this,&ASBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASBaseCharacter::OnGroundLanded);
	//WeaponComponent->SpawnWeapon();
}

// Called every frame
void ASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//const auto Health = HealthComponent->GetHealth();
	

	//TakeDamage(0.1f,FDamageEvent(),Controller,this);
}

// Called to bind functionality to input
void ASBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASBaseCharacter::OnStopRunning);
	//PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USWeaponComponent::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USWeaponComponent::StopFire);
}

bool ASBaseCharacter::IsRunning() const
{
	return WantsToRuns && IsMovingFarward && !GetVelocity().IsZero();
}

float ASBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degrees : Degrees *FMath::Sign(CrossProduct.Z);
}

void ASBaseCharacter::MoveForward(float Amount)
{
	IsMovingFarward = Amount > 0.0f;
	if (Amount == 0.0f)return;
	AddMovementInput(GetActorForwardVector(),Amount);
}

void ASBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASBaseCharacter::OnStartRunning()
{
	WantsToRuns = true;
}

void ASBaseCharacter::OnStopRunning()
{
	WantsToRuns = false;
}

void ASBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog,Display,TEXT("Player %s is dead"), *GetName());

	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ASBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = GetCharacterMovement()->Velocity.Z * -1;
	UE_LOG(BaseCharacterLog,Display,TEXT("On landed: %f"),FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X)return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("FinalDamage: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{},nullptr,nullptr);
}
