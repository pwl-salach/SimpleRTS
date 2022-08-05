// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GenericPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERTS_API AGenericPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int8 GetTeamNumber();
	FLinearColor GetTeamColour();
};
