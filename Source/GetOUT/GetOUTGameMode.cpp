// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GetOUTGameMode.h"
#include "GetOUTHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGetOUTGameMode::AGetOUTGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/NPC/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGetOUTHUD::StaticClass();
}
