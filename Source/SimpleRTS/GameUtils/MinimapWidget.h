// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERTS_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

public: 

	UMinimapWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

private:

	bool bCanEverTick : 1;
	class USceneCaptureComponent2D* MinimapCamera;
 	class UMaterial* mSnapshotMaterial;
	class UCanvasPanel* RootWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* TargetImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* ItemTitle = nullptr;

	class UMaterialInstanceDynamic *dynamicMaterial;
	class USceneCaptureComponent2D *MinimapCaptureComponent;
	class ASceneCapture2D *MinimapCaptureActor;
	class UTextureRenderTarget2D *RenderTarget;
};
