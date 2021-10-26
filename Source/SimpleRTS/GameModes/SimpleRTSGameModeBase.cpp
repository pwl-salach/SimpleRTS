// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleRTSGameModeBase.h"
#include "../GameUtils/CameraPawn.h"
#include "../GameUtils/MousePlayerController.h"
#include "../GameUtils/InGameHUD.h"

void ASimpleRTSGameModeBase::BeginPlay()
{
}

void ASimpleRTSGameModeBase::ActorDied(AActor *DeadActor)
{
}

void ASimpleRTSGameModeBase::HandleGameStart()
{
}

void ASimpleRTSGameModeBase::HandleGameOver(bool PlayerWon)
{
}

ASimpleRTSGameModeBase::ASimpleRTSGameModeBase()
{
    DefaultPawnClass = ACameraPawn::StaticClass();
    PlayerControllerClass = AMousePlayerController::StaticClass();
    HUDClass = AInGameHUD::StaticClass();
}
