// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Landscape.h"
// #include "LandscapeInfo.h"
#include "Blueprint/WidgetTree.h"
#include "Camera/CameraTypes.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/TextBlock.h"
#include "DrawDebugHelpers.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GenericPlatform/GenericPlatformMath.h"

UMinimapWidget::UMinimapWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
    ConstructorHelpers::FObjectFinder<UMaterial> BaseMaterialFinder(TEXT("Material'/Game/Blueprints/UI/Materials/MinimapMaterial'"));
    BaseMaterial = (UMaterial *)BaseMaterialFinder.Object;

    RenderTarget = NewObject<UTextureRenderTarget2D>();
}

void UMinimapWidget::NativeConstruct() {
    Super::NativeConstruct();

    TArray<AActor *> lands;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscape::StaticClass(), lands);
    float MinX = MAX_flt, MinY = MAX_flt, MaxX = MIN_flt, MaxY = MIN_flt;
    for (AActor *IterActor : lands) {
        ALandscape *CurrentLandscape = Cast<ALandscape>(IterActor);
        if (CurrentLandscape != nullptr) {
#if WITH_EDITOR
            // GetBoundingRect is not available outside editor
            FIntRect LandscapeBounderis = CurrentLandscape->GetBoundingRect();
            FVector LandscapeScale = CurrentLandscape->GetActorScale3D();
            MinX = FMath::Min(LandscapeBounderis.Min.X * LandscapeScale.X, MinX);
            MaxX = FMath::Max(LandscapeBounderis.Max.X * LandscapeScale.X, MaxX);
            MinY = FMath::Min(LandscapeBounderis.Min.Y * LandscapeScale.Y, MinY);
            MaxY = FMath::Max(LandscapeBounderis.Max.Y * LandscapeScale.Y, MaxY);
#endif
        }
    }

    ASceneCapture2D *CaptureActor = (ASceneCapture2D *)GetWorld()->SpawnActor<ASceneCapture2D>(ASceneCapture2D::StaticClass());
    Camera = CaptureActor->GetCaptureComponent2D();
    Camera->RegisterComponent();
    Camera->bCaptureEveryFrame = false;
    Camera->ProjectionType = ECameraProjectionMode::Orthographic;
    Camera->OrthoWidth = FMath::Max(MaxX - MinX, MaxY - MinY);
    // float CameraHeight = 1000000;  // just to ensure that it will be above all other objects
    // Camera->SceneViewExtensions

    // Camera->ProjectionType = ECameraProjectionMode::Perspective;
    Camera->FOVAngle = 90;
    float CameraHeight = FMath::Max(MaxX - MinX, MaxY - MinY) / 2; // Max/2 as tg(FOV/2) = 1, so height is a half of max map dimension

    FVector CameraLocation = FVector((MaxX + MinX) / 2, (MaxY + MinY) / 2, CameraHeight);
    FRotator CameraRotation = FRotator(-90.f, 0.f, 0.f);
    FTransform CameraTransform = FTransform(CameraRotation, CameraLocation);

    Camera->SetWorldTransform(CameraTransform);
}

void UMinimapWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (RenderTarget) {
        RenderTarget->ClearColor = FLinearColor::Blue;
        RenderTarget->InitAutoFormat(512, 512);
        RenderTarget->UpdateResourceImmediate();

        Camera->TextureTarget = RenderTarget;
        Camera->CaptureScene();
        Material = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        Material->SetTextureParameterValue(FName("Texture"), RenderTarget);

        TargetImage->SetBrushFromMaterial(Material);
    }
}
