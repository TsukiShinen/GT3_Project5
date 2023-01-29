// Copyright Epic Games, Inc. All Rights Reserved.

#include "GT3_Project5_Gr1GameMode.h"
#include "GT3_Project5_Gr1Character.h"
#include "UObject/ConstructorHelpers.h"

AGT3_Project5_Gr1GameMode::AGT3_Project5_Gr1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
