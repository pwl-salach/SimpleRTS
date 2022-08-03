// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

enum class EActionTargetType : uint8;

/**
 *
 */
UCLASS()
class SIMPLERTS_API AMousePlayerController : public APlayerController {
    GENERATED_BODY()
public:
    AMousePlayerController();

    bool IsSelecting();
    FVector2D GetSelectionStartingPoint();
    FVector2D GetSelectionEndingPoint();

protected:
private:
    uint8 MaxSelectedObjects;
    TArray<AActor *> SelectedObjects;

    virtual void SetupInputComponent() override;

    bool SelectionInProgress;
    FVector2D SelectionStartingPoint;
    FVector2D SelectionEndingPoint;
    void StartSelection();
    void EndSelection();
    void FilterSelection(TArray<AActor *> UnfilteredSelected);

    uint8 GetActorPriority(const AActor &Actor);

    void HandleActionClick();
    FVector2D GetCursorLocation();
    FVector GetWorldCursorLocation(FVector2D ScreenCursorLocation);
    EActionTargetType GetActionTargetType(FVector2D CursorLocation);

    TArray<FVector> CalculateFormationCoordinates(FVector CenterLocation, uint8 FormationSize);
};
