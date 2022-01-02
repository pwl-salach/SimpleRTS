// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UUserWidget;
class USelectionWidget;
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
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;  // is it needed?

	TArray<AActor*> GetSelectedActors();
	void UpdateUserSelection(TArray<AActor*> Selected);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMinimapWidget* Minimap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USelectionWidget* Selection;

	TSubclassOf<UMinimapWidget> MinimapClass;
	TSubclassOf<USelectionWidget> SelectionClass;

	TArray<AActor*> SelectedObjects;

	void AddWidget(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, FName WidgetName);

};
