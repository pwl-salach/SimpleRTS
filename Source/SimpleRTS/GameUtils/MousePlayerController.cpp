// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.h"
#include "../Components/SelectableComponent.h"

AMousePlayerController::AMousePlayerController() 
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
    bEnableMouseOverEvents = true;
}

void AMousePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    check(InputComponent);

    if (InputComponent != NULL)
	{
		InputComponent->BindAction("Selection", EInputEvent::IE_Pressed, this, &AMousePlayerController::StartSelection);
		InputComponent->BindAction("Selection", EInputEvent::IE_Released, this, &AMousePlayerController::EndSelection);
	}
}

void AMousePlayerController::StartSelection() 
{
    SelectionInProgress = true;
    UGameViewportClient* GameViewport = GEngine->GameViewport;
    if(GameViewport != nullptr)
    {
        GameViewport->GetMousePosition(SelectionStartingPoint);
    } 
    else 
    {
        UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));    
    }
}

void AMousePlayerController::EndSelection() 
{
    UGameViewportClient* GameViewport = GEngine->GameViewport;
    if(GameViewport != nullptr)
    {
        GameViewport->GetMousePosition(SelectionEndingPoint);
    } 
    else 
    {
        UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));    
    }
    AInGameHUD* HUD = Cast<AInGameHUD>(GetHUD());
    SelectedObjects = HUD->GetSelectedActors();
    for(AActor* Iter : SelectedObjects){
        TArray<UActorComponent*> SelectableRepresentation = Iter->GetComponentsByClass(USelectableComponent::StaticClass());
        if(SelectableRepresentation.Num() > 0){
            UE_LOG(LogTemp, Warning, TEXT("QWE: %s"), *Iter->GetName());   
        }
    }
    SelectionInProgress = false;
}

bool AMousePlayerController::IsSelecting() 
{
    return SelectionInProgress;
}

FVector2D AMousePlayerController::GetSelectionStartingPoint() 
{
    return SelectionStartingPoint;
}

FVector2D AMousePlayerController::GetSelectionEndingPoint() 
{
    if(SelectionInProgress)
    {
        FVector2D TmpSelectionEndingPoint(0.f, 0.f);
        UGameViewportClient* GameViewport = GEngine->GameViewport;
        if(GameViewport != nullptr){
            GameViewport->GetMousePosition(TmpSelectionEndingPoint);
        } else {
            UE_LOG(LogTemp, Error, TEXT("GameViewport not set"));    
        }
        return TmpSelectionEndingPoint;
    }
    else 
    {
        return SelectionEndingPoint;
    }
}
