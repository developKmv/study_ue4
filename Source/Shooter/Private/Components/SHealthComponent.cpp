// Shooter Games DEV


#include "Components/SHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
//#include "Dev/SFireDamageType.h"
//#include "Dev/SIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All)

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	//OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::OnTakeAnyDamageHandle);
	}

	//OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::OnTakeAnyDamageHandle);
	
}


void USHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//UE_LOG(BaseCharacterLog, Display, TEXT("Damage: %f"), Damage);
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	SetHealth(Health-Damage);
	//OnHealthChanged.Broadcast(Health);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USHealthComponent::HealUpdate,HealUpdateTime,true,HealDelay);
	}

	//UE_LOG(LogHealthComponent,Display,TEXT("Damage: %f"),Damage);

	/*if (DamageType)
	{
		if (DamageType->IsA<USFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("So hooooooooooot!!!"));
		}
		else if (DamageType->IsA<USIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("So coooooooooooooold!!!"));
		}
	}*/
}

void USHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	//OnHealthChanged.Broadcast(Health);

	if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
