// Copyright Epic Games, Inc. All Rights Reserved.

#include "AfterWaterDemoGameMode.h"
#include "AfterWaterDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAfterWaterDemoGameMode::AAfterWaterDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
