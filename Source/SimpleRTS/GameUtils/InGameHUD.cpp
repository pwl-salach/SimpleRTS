// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"
#include "MinimapWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "MousePlayerController.h"

AInGameHUD::AInGameHUD()
{
    static ConstructorHelpers::FClassFinder<UMinimapWidget> MinimapCls(TEXT("/Game/Blueprints/UI/Widgets/BP_Minimap"));
    MinimapClass = MinimapCls.Class;
}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!ensure(MinimapClass != nullptr))
        return;
    Minimap = CreateWidget<UMinimapWidget>(GetWorld()->GetFirstPlayerController(), MinimapClass, "Minimap");
    if (Minimap)
    {
        Minimap->AddToViewport();
        UE_LOG(LogTemp, Warning, TEXT("Minimap widget added to viewport"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Minimap widget wasn't created"));
    }
}

void AInGameHUD::DrawHUD()
{
    Super::DrawHUD();
    AMousePlayerController *Controller = Cast<AMousePlayerController>(GetOwningPlayerController());
    if (Controller->IsSelecting())
    {
        auto StartingPoint = Controller->GetSelectionStartingPoint();
        auto EndingPoint = Controller->GetSelectionEndingPoint();
        DrawRect(FLinearColor(0.f, 0.7f, 0.5f, 0.2f), StartingPoint.X, StartingPoint.Y,
                 EndingPoint.X - StartingPoint.X,
                 EndingPoint.Y - StartingPoint.Y);
        SelectedObjects.Empty();
        GetActorsInSelectionRectangle<AActor>(StartingPoint, EndingPoint, SelectedObjects, false);
    }
}

void AInGameHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}



TArray<AActor*> AInGameHUD::GetSelectedActors()
{

    return SelectedObjects;
}
