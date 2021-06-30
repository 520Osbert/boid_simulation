// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnderWaterGameMode.h"
#include "UnderWaterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnderWaterGameMode::AUnderWaterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
