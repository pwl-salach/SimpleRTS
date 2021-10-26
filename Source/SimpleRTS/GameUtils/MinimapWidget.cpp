// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Landscape.h"
// #include "LandscapeInfo.h"
#include "DrawDebugHelpers.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/SceneCapture2D.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

UMinimapWidget::UMinimapWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{

    // // Creating a new material from the base one and setting the render target as texture
    ConstructorHelpers::FObjectFinder<UMaterial> snapshotMaterialFinder(TEXT("Material'/Game/Blueprints/UI/Materials/MinimapMaterial'"));

    // Need to cast the pointer. The mSnapshotMaterial has type UMaterial*
    mSnapshotMaterial = (UMaterial *)snapshotMaterialFinder.Object;
    RenderTarget = NewObject<UTextureRenderTarget2D>();
    bHasScriptImplementedTick = 0;
    // bCanEverTick  = 1;
}

void UMinimapWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TArray<AActor *> lands;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscape::StaticClass(), lands);
    float MinX = MAX_flt, MinY = MAX_flt, MaxX = MIN_flt, MaxY = MIN_flt;
    for (AActor *IterActor : lands)
    {
        ALandscape *CurrentLandscape = Cast<ALandscape>(IterActor);
        if (CurrentLandscape != nullptr)
        {
#if WITH_EDITOR
            FIntRect LandscapeBounderis = CurrentLandscape->GetBoundingRect();
            FVector LandscapeScale = CurrentLandscape->GetActorScale3D();
            MinX = FMath::Min(LandscapeBounderis.Min.X * LandscapeScale.X, MinX);
            MaxX = FMath::Max(LandscapeBounderis.Max.X * LandscapeScale.X, MaxX);
            MinY = FMath::Min(LandscapeBounderis.Min.Y * LandscapeScale.Y, MinY);
            MaxY = FMath::Max(LandscapeBounderis.Max.Y * LandscapeScale.Y, MaxY);
#endif
        }
    }

    FVector MinimapCameraLocation = FVector((MaxX + MinX) / 2, (MaxY + MinY) / 2, 1000);
    DrawDebugSphere(GetWorld(), MinimapCameraLocation, 10.f, 1, FColor::Red, true);
    UE_LOG(LogTemp, Log, TEXT("Adding a Scene Capture Component in location: %s"), *MinimapCameraLocation.ToString());

    MinimapCaptureActor = (ASceneCapture2D *)GetWorld()->SpawnActor<ASceneCapture2D>(ASceneCapture2D::StaticClass());
    FRotator MinimapCameraRotation = FRotator(-90.f, 0.f, 0.f);
    FTransform MinimapCameraTransform = FTransform(MinimapCameraRotation, MinimapCameraLocation);
    MinimapCaptureComponent = MinimapCaptureActor->GetCaptureComponent2D();
    MinimapCaptureComponent->RegisterComponent();
    MinimapCaptureComponent->SetWorldTransform(MinimapCameraTransform);
    MinimapCaptureComponent->bCaptureEveryFrame = true;

    // COPIED FROM NET
    if (RenderTarget)
    {
        RenderTarget->ClearColor = FLinearColor::Blue;
        RenderTarget->InitAutoFormat(512, 512);
        RenderTarget->UpdateResourceImmediate();

        MinimapCaptureComponent->TextureTarget = RenderTarget;
        // MinimapCaptureComponent->UpdateContent();
        MinimapCaptureComponent->CaptureScene();    

        // FTextureRenderTarget2DResource* textureTargetResource = (FTextureRenderTarget2DResource*)RenderTarget->Resource;

        // auto imageRendered = MinimapCaptureComponent->TextureTarget->ConstructTexture2D(this, "CameraImage", EObjectFlags::RF_NoFlags, CTF_DeferCompression);


        dynamicMaterial = UMaterialInstanceDynamic::Create(mSnapshotMaterial, this);
        dynamicMaterial->SetTextureParameterValue(FName("Texture"), RenderTarget);

 
        // TargetImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
        // TargetImage->SetBrushFromTexture(imageRendered);
        // TargetImage->SetBrushFromMaterial(dynamicMaterial);
	    if (TargetImage == nullptr)
	    {
             UE_LOG(LogTemp, Error, TEXT("TargetImage EMPTY"));
            // ItemTitle->SetText(FText::FromString(TEXT("QWEAD")));
        } else {
            TargetImage->SetBrushFromMaterial(dynamicMaterial);
            // TargetImage->SetBrushFromTexture(imageRendered);
        }
        // RootWidget = Cast<UPanelWidget>(GetRootWidget());
        // if (RootWidget)
        // {
            // RootWidget->AddChild(TargetImage);
        // }
        // else
        // {
            // UE_LOG(LogTemp, Error, TEXT("RootWidget EMPTY"));
            // RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootWidget"));
            // UCanvasPanelSlot *RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);
            // if (RootWidgetSlot)
            // {
        //         RootWidgetSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
        //         RootWidgetSlot->SetOffsets(FMargin(0.f, 0.f));
        //         RootWidgetSlot->SetSize(FVector2D(300.f, 2000.f));
        //     }
        //     if (RootWidget)
        //     {
        //         UE_LOG(LogTemp, Error, TEXT("RootWidget CREATED"));
        //         TargetImage->SetBrushSize(FVector2D(100.f, 100.f));
        //         RootWidget->AddChild(TargetImage);
        //         UCanvasPanelSlot* ImageSlot = Cast<UCanvasPanelSlot>(TargetImage->Slot);
        //         if (ImageSlot)
        //         {   
        //             UE_LOG(LogTemp, Error, TEXT("IMAGE position %s"), *ImageSlot->GetPosition().ToString());
        //             UE_LOG(LogTemp, Error, TEXT("IMAGE size %s"), *ImageSlot->GetSize().ToString());
        //             ImageSlot->SetSize(FVector2D(1000.f, 500.f));
        //             UE_LOG(LogTemp, Error, TEXT("IMAGE size %s"), *ImageSlot->GetSize().ToString());
        //         }
        //         UE_LOG(LogTemp, Error, TEXT("IMAGE SIZE %s"),*TargetImage->GetDesiredSize().ToString());
        //     }
        // }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RenderTarget EMPTY"));
    }
    // auto MyButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
    // RootWidget->AddChild(MyButton);
    // WidgetTree->RootWidget = RootWidget;

    // // Telling the UMG to set the new material
    // SetTextureMaterial(0, dynamicMaterial);
}
