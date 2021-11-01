// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERTS_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMousePlayerController();
	
	bool IsSelecting();
	FVector2D GetSelectionStartingPoint();
	FVector2D GetSelectionEndingPoint();
protected:

private:

	TArray<AActor*> SelectedObjects;

	virtual void SetupInputComponent() override;


	bool SelectionInProgress;
	FVector2D SelectionStartingPoint;
	FVector2D SelectionEndingPoint;
	void StartSelection();
	void EndSelection();
};
