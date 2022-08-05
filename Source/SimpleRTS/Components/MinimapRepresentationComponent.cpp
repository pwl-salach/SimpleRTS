// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapRepresentationComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "../GameUtils/GenericPlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMinimapRepresentationComponent::UMinimapRepresentationComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<UMaterial> MinimapMaterialFinder(TEXT(
        // "/Game/Blueprints/UI/Materials/MinimapRepresentationMaterialInstance.MinimapRepresentationMaterialInstance"));
        "/Game/Blueprints/UI/Materials/MinimapRepresentationMaterial.MinimapRepresentationMaterial"));
    MinimapMaterial = (UMaterial *)MinimapMaterialFinder.Object;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MinimapSpriteFinder(TEXT("/Engine/BasicShapes/Plane.Plane"));
    MinimapSprite = (UStaticMesh *)MinimapSpriteFinder.Object;
    if (MinimapSprite == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("MinimapSprite not found"));
    }
    SetStaticMesh(MinimapSprite);
    SetVisibleInSceneCaptureOnly(true);
    // ...
}

// Called when the game starts
void UMinimapRepresentationComponent::BeginPlay() {
    Super::BeginPlay();

    // ...
}

// Called every frame
void UMinimapRepresentationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UMinimapRepresentationComponent::OnAttachmentChanged() {
    if (MinimapMaterialInstance == nullptr){
        FString MID_Name = FString::Printf(TEXT("%s_MaterialInstance"), *GetOwner()->GetName());
        MinimapMaterialInstance = UMaterialInstanceDynamic::Create(MinimapMaterial, this, *MID_Name);
        SetMaterial(0, MinimapMaterialInstance);
    }


    TArray<USceneComponent *> Parents;
    GetParentComponents(Parents);
    if (!Parents.IsEmpty()) {
        SetupLocation(Parents[0]);
    }
}

void UMinimapRepresentationComponent::SetupLocation(USceneComponent *InParent) {
    float HalfHeight;
    float Radius;
    InParent->CalcBoundingCylinder(Radius, HalfHeight);
    FVector Scale = InParent->GetComponentScale();
    FVector Location = FVector(0, 0, HalfHeight / Scale.Z + 10);
    // SetRelativeLocation(FVector(0, 0, 0), false);
    SetRelativeLocation(Location, false);
    FLinearColor a = MinimapMaterialInstance->K2_GetVectorParameterValue("TeamColor");
    // auto ddd = UGameplayStatics::GetPlayerState();
    // AGenericPlayerState* MyPlayerState = Cast<AGenericPlayerState>(ddd);
    MinimapMaterialInstance->SetVectorParameterValue("TeamColor", FLinearColor(1, 0, 0.5, 1));
    FLinearColor b = MinimapMaterialInstance->K2_GetVectorParameterValue("TeamColor");
    // MinimapMaterialInstance->SetVectorParameterValueInternal("TeamColor", FLinearColor(1,0,1,1));
    SetupForUnitOwner();    
}

void UMinimapRepresentationComponent::SetupForBuildingOwner() {
}

void UMinimapRepresentationComponent::SetupForHeroOwner() {
}

void UMinimapRepresentationComponent::SetupForUnitOwner() {
}
