// Shooter Games DEV

#include "SGameModeBase.h"
#include "Player/SBaseCharacter.h"
#include "Player/SPlayerController.h"
#include "UI/SHUD.h"

ASGameModeBase::ASGameModeBase()
{
	DefaultPawnClass = ASBaseCharacter::StaticClass();
	PlayerControllerClass = ASPlayerController::StaticClass();
	HUDClass = ASHUD::StaticClass();
}