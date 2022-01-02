// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectionWidget.h"
//
#include "../Components/SelectableComponent.h"
// UE
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"


USelectionWidget::USelectionWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("USelectionWidget::USelectionWidget"));
}

void USelectionWidget::NativeConstruct()
{
    UE_LOG(LogTemp, Warning, TEXT("USelectionWidget::NativeConstruct"));
    Super::NativeConstruct();
    // TargetWidget = Cast<UPanelWidget>(GetTargetWidget());
}

void USelectionWidget::Update(TArray<AActor*> SelectedObjects) 
{
    ClearSelection();
    if(SelectedObjects.Num() == 0){
        UE_LOG(LogTemp, Warning, TEXT("Updating  USelectionWidget with no selection"));
    } else if (SelectedObjects.Num() == 1){
        UE_LOG(LogTemp, Warning, TEXT("Updating  USelectionWidget with single object selected"));
        SingleAvatar = CreateAvatar(SelectedObjects[0]);
        TargetWidget->AddChild(SingleAvatar);
        UCanvasPanelSlot* AvatarSlot = Cast<UCanvasPanelSlot>(SingleAvatar->Slot);
        if (AvatarSlot)
        {
            AvatarSlot->SetSize(FVector2D(SingleAvatarWidth, SingleAvatarHeight));
            AvatarSlot->SetPosition(FVector2D(FIntPoint(HorizontalMargin, VerticalMargin)));
        }
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Updating  USelectionWidget with multiple objects selected"));
        uint8 Index = 0;
        for(AActor* IterActor : SelectedObjects){
            UImage* IterAvatar = CreateAvatar(IterActor);
            TargetWidget->AddChild(IterAvatar);
            MultipleAvatars.Add(IterAvatar);
            UCanvasPanelSlot* AvatarSlot = Cast<UCanvasPanelSlot>(IterAvatar->Slot);
            if (AvatarSlot)
            {
                AvatarSlot->SetSize(FVector2D(IterAvatarWidth, IterAvatarHeight));
                AvatarSlot->SetPosition(FVector2D(FIntPoint(Index * (IterAvatarWidth + HorizontalMargin), VerticalMargin)));
            }
            Index++;
        }
    }
}

void USelectionWidget::ClearSelection() 
{
    for(UImage* IterAvatar : MultipleAvatars){
        IterAvatar = nullptr;
    }
    MultipleAvatars.Empty();
    if(SingleAvatar != nullptr){
        SingleAvatar = nullptr;
    }
    TargetWidget->ClearChildren();
}

UImage* USelectionWidget::CreateAvatar(AActor* SelectedActor) 
{
    TArray<USelectableComponent*> SelectableRepresentation;
    UImage* IterAvatar;
    SelectedActor->GetComponents(SelectableRepresentation);
    if(SelectableRepresentation.Num() != 1){
        UE_LOG(LogTemp, Error, TEXT("Wrong USelectableComponent setup of Actor: %s. Number of attached components: %d"), *SelectedActor->GetName(), SelectableRepresentation.Num())
    }
    USelectableComponent* IterComponent = SelectableRepresentation[0];
    FString AvatarName = FString::Printf(TEXT("%s_Avatar"), *SelectedActor->GetName());
    if(WidgetTree == nullptr){
        UE_LOG(LogTemp, Error, TEXT("EMPTY WidgetTree"));
    }
    IterAvatar = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *AvatarName);
    IterAvatar->SetBrushFromTexture(IterComponent->GetAvatar());
    return IterAvatar;
}
