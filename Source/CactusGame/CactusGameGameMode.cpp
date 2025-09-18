// Copyright Epic Games, Inc. All Rights Reserved.

#include "CactusGameGameMode.h"
#include "CactusGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACactusGameGameMode::ACactusGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
