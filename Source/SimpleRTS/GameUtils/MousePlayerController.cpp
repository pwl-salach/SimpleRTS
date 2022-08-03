// Fill out your copyright notice in the Description page of Project Settings.

#include "MousePlayerController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/HUD.h"

#include "../Components/SelectableComponent.h"
#include "../GUI/InGameHUD.h"
#include "../GameUtils/CameraPawn.h"
#include "../GameUtils/Enums/ActionTargetType.h"
#include "../Units/BaseUnit.h"


AMousePlayerController::AMousePlayerController() {
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
    bEnableMouseOverEvents = true;
    MaxSelectedObjects = 12;
}

void AMousePlayerController::SetupInputComponent() {
    Super::SetupInputComponent();
    check(InputComponent);

    if (InputComponent != NULL) {
        InputComponent->BindAction("Selection", EInputEvent::IE_Pressed, this, &AMousePlayerController::StartSelection);
        InputComponent->BindAction("Selection", EInputEvent::IE_Released, this, &AMousePlayerController::EndSelection);
        InputComponent->BindAction("ActionClick", EInputEvent::IE_Pressed, this, &AMousePlayerController::HandleActionClick);
    }
}

void AMousePlayerController::StartSelection() {
    SelectionInProgress = true;
    UGameViewportClient *GameViewport = GEngine->GameViewport;
    if (GameViewport != nullptr) {
        GameViewport->GetMousePosition(SelectionStartingPoint);
    } else {
        UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));
    }
}

void AMousePlayerController::EndSelection() {
    UGameViewportClient *GameViewport = GEngine->GameViewport;
    if (GameViewport != nullptr) {
        GameViewport->GetMousePosition(SelectionEndingPoint);
    } else {
        UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));
    }
    AInGameHUD *HUD = Cast<AInGameHUD>(GetHUD());
    TArray<AActor *> UnfilteredSelected = HUD->GetSelectedActors();
    FilterSelection(UnfilteredSelected);
    HUD->UpdateUserSelection(SelectedObjects);
    SelectionInProgress = false;
}

void AMousePlayerController::FilterSelection(TArray<AActor *> UnfilteredSelected) {
    UnfilteredSelected.Sort([this](const AActor &Actor1, const AActor &Actor2) { return GetActorPriority(Actor1) > GetActorPriority(Actor2); });
    SelectedObjects.Empty();
    uint8 MaxPriorityTier = 1;
    for (AActor *IterActor : UnfilteredSelected) {
        uint8 TempPriorityTier = GetActorPriority(*IterActor) / 10;
        if (SelectedObjects.Num() == MaxSelectedObjects || TempPriorityTier < MaxPriorityTier) {
            break;
        }
        SelectedObjects.Add(IterActor);
        MaxPriorityTier = TempPriorityTier;
    }
}

uint8 AMousePlayerController::GetActorPriority(const AActor &Actor) {
    USelectableComponent *SelectableComponent = Cast<USelectableComponent>(Actor.GetComponentByClass(USelectableComponent::StaticClass()));
    if (SelectableComponent != nullptr) {
        return SelectableComponent->GetPriority();
    } else {
        return 0;
    }
}

bool AMousePlayerController::IsSelecting() {
    return SelectionInProgress;
}

FVector2D AMousePlayerController::GetSelectionStartingPoint() {
    return SelectionStartingPoint;
}

FVector2D AMousePlayerController::GetSelectionEndingPoint() {
    if (SelectionInProgress) {
        FVector2D TmpSelectionEndingPoint(0.f, 0.f);
        UGameViewportClient *GameViewport = GEngine->GameViewport;
        if (GameViewport != nullptr) {
            GameViewport->GetMousePosition(TmpSelectionEndingPoint);
        } else {
            UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));
        }
        return TmpSelectionEndingPoint;
    } else {
        return SelectionEndingPoint;
    }
}

void AMousePlayerController::HandleActionClick() {
    UE_LOG(LogTemp, Warning, TEXT("RIGHT CLICK"));
    if (SelectedObjects.IsEmpty()) {
        return;
    }
    FVector2D CursorLocation = GetCursorLocation();
    FVector WorldClickLocation = GetWorldCursorLocation(CursorLocation);

    DrawDebugPoint(GetWorld(), WorldClickLocation, 10, FColor(52, 220, 239), false, 3.0f);
    ProjectWorldLocationToScreen(WorldClickLocation, CursorLocation);

    EActionTargetType TargetType = GetActionTargetType(CursorLocation);

    TArray<FVector> FormationCoordinates = CalculateFormationCoordinates(WorldClickLocation, SelectedObjects.Num());

    for (uint8 LoopIndex = 0; LoopIndex < SelectedObjects.Num(); LoopIndex++) {
        AActor* IterActor = SelectedObjects[LoopIndex];
        FVector IterCoords = FormationCoordinates[LoopIndex];
        // USelectableComponent *SelectableComponent = Cast<USelectableComponent>(IterActor->GetComponentByClass(USelectableComponent::StaticClass()));
        DrawDebugPoint(GetWorld(), IterCoords, 10, FColor(150, 120, 130), false, 3.0f);
        ABaseUnit* UnitActor = Cast<ABaseUnit>(IterActor);
        if(UnitActor != nullptr){
            UnitActor->MoveToLocation(IterCoords);
        }
    }
}

FVector2D AMousePlayerController::GetCursorLocation() {
    FVector2D CursorLocation(0.f, 0.f);
    UGameViewportClient *GameViewport = GEngine->GameViewport;
    if (GameViewport != nullptr) {
        GameViewport->GetMousePosition(CursorLocation);
    } else {
        UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));
    }
    return CursorLocation;
}

FVector AMousePlayerController::GetWorldCursorLocation(FVector2D CursorLocation) {
    FHitResult HitResult;
    FCollisionQueryParams TraceParams;
    GetHitResultAtScreenPosition(CursorLocation, ECC_Visibility, TraceParams, HitResult);
    return HitResult.Location;
}

EActionTargetType AMousePlayerController::GetActionTargetType(FVector2D CursorLocation) {
    return EActionTargetType::Tarrain;
}

TArray<FVector> AMousePlayerController::CalculateFormationCoordinates(FVector CenterLocation, uint8 FormationSize) {
    uint8 RowsCount;
    // RowsCount should be dependant on MaxSelectedObjects
    if (FormationSize < 3) {
        RowsCount = 1;
    } else if (FormationSize < 7) {
        RowsCount = 2;
    } else {
        RowsCount = 3;
    }
    uint8 ObjectsPerRow = FormationSize / RowsCount;
    uint8 LeftoverObjects = FormationSize % RowsCount;

    TArray<uint8> RowsLengths;
    RowsLengths.Init(ObjectsPerRow, RowsCount);
    for (int i = 0; i < LeftoverObjects; i++) {
        if(2*i > RowsCount){
            RowsLengths[2*i-RowsCount]++;
        } else {
            RowsLengths[2*i]++;
        }
    }
    float PositionsSpacing = 100.f;
    float CenterRow = float(RowsCount - 1) / 2 ;
    uint8 FirstRowSize = RowsLengths[0];
    float CenterPosition = float(FirstRowSize - 1) / 2;
    TArray<FVector> FormationCoordinates;

    for (uint8 RowIndex = 0; RowIndex < RowsCount; RowIndex++){
        float YCoord = CenterLocation.Y - (RowIndex - CenterRow) * PositionsSpacing;
        float RowOffset = (RowIndex % 2 == 0) ? 0.f : - PositionsSpacing / 2;
        uint8 RowSize = RowsLengths[RowIndex];
        for(uint8 PositionIndex = 0; PositionIndex < RowSize; PositionIndex++){
            FVector Position;
            Position.X = CenterLocation.X - (PositionIndex - CenterPosition) * PositionsSpacing + RowOffset;
            Position.Y = YCoord;
            Position.Z = 5000;
            FVector NullPosition = FVector(Position.X, Position.Y, 0);
            FCollisionQueryParams TraceParams;
	        FHitResult Hit;
	        bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Position, NullPosition, ECC_WorldStatic, TraceParams);
            Position.Z = Hit.ImpactPoint.Z;
            FormationCoordinates.Add(Position);
        }
    }

    return FormationCoordinates;
}
