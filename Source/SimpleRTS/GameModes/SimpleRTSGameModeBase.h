// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleRTSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERTS_API ASimpleRTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimpleRTSGameModeBase();
	
private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

public:
	void ActorDied(AActor *DeadActor);
};
