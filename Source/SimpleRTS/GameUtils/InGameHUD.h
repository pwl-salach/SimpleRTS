// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"


class UMinimapWidget;

/**
 * 
 */
UCLASS()
class SIMPLERTS_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	UMinimapWidget* Minimap;

	TSubclassOf<class UMinimapWidget> MinimapClass;
};
