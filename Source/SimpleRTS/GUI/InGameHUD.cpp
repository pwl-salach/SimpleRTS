// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"
// other widgets
#include "MinimapWidget.h"
#include "SelectionWidget.h"
// utils
#include "../GameUtils/MousePlayerController.h"
// UE
#include "UObject/ConstructorHelpers.h"


AInGameHUD::AInGameHUD()
{
    static ConstructorHelpers::FClassFinder<UMinimapWidget> MinimapCls(TEXT("/Game/Blueprints/UI/Widgets/BP_Minimap"));
    MinimapClass = MinimapCls.Class;

    static ConstructorHelpers::FClassFinder<USelectionWidget> SelectionCls(TEXT("/Game/Blueprints/UI/Widgets/BP_Selection"));
    SelectionClass = SelectionCls.Class;
}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();

    // AddWidget(Minimap, MinimapClass, "Minimap");

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


    // AddWidget(Selection, SelectionClass, "Selection");

    if (!ensure(SelectionClass != nullptr))
        return;
    Selection = CreateWidget<USelectionWidget>(GetWorld()->GetFirstPlayerController(), SelectionClass, "Selection");
    if (Selection)
    {
        Selection->AddToViewport();
        UE_LOG(LogTemp, Warning, TEXT("Selection widget added to viewport"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Selection widget wasn't created"));
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

void AInGameHUD::UpdateUserSelection(TArray<AActor*> Selected) 
{
    Selection->Update(Selected);
}

void AInGameHUD::AddWidget(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, FName WidgetName) 
{
    if (!ensure(WidgetClass != nullptr))
        return;
    Widget = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetClass, WidgetName);
    if (Widget)
    {
        Widget->AddToViewport();
        UE_LOG(LogTemp, Warning, TEXT("%s widget added to viewport"), *WidgetName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s widget wasn't created"), *WidgetName.ToString());
    }
}
