// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJamITBAGameMode.h"
#include "GameJamITBACharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameJamITBAGameMode::AGameJamITBAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
