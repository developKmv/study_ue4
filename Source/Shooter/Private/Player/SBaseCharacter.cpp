// Shooter Games DEV


#include "Player/SBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SCharacterMovementComponent.h"

// Sets default values
ASBaseCharacter::ASBaseCharacter(const FObjectInitializer& ObjInit): Super(ObjInit.SetDefaultSubobjectClass<USCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void ASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


