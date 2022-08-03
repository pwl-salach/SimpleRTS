// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectionWidget.generated.h"

class APlayerController;
class UImage;
class UPanelWidget;
/**
 * 
 */
UCLASS()
class SIMPLERTS_API USelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USelectionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	// virtual TSharedRef<SWidget> RebuildWidget() override;

	void Update(TArray<AActor*> Objects);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UPanelWidget* TargetWidget;


	UImage* SingleAvatar;
	TArray<UImage*> MultipleAvatars;

	void ClearSelection();
	UImage* CreateAvatar(AActor* SelectedActor);

	// FIXME: hardcoded values - make them dependant on screen resolution
	float SingleAvatarHeight = 300;
	float SingleAvatarWidth = 200;
	
	float IterAvatarHeight = 150;
	float IterAvatarWidth = 90;
	float VerticalMargin = 50;
	float HorizontalMargin = 50;
	uint8 MultiSelectionRowLength = 5;
};
