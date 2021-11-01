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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* TargetImage;

	class USceneCaptureComponent2D* Camera;
 	class UMaterial* BaseMaterial;
	class UMaterialInstanceDynamic *Material;
	class UTextureRenderTarget2D *RenderTarget;
};
