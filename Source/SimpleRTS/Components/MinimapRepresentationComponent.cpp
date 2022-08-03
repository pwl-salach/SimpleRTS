// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimapRepresentationComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UMinimapRepresentationComponent::UMinimapRepresentationComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MinimapSpriteFinder(TEXT("/Engine/BasicShapes/Plane.Plane"));
    MinimapSprite = (UStaticMesh *)MinimapSpriteFinder.Object;
    if (MinimapSprite == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("MinimapSprite not found"));
    }
    SetStaticMesh(MinimapSprite);

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
    TArray<USceneComponent *> Parents;
    GetParentComponents(Parents);
    if (!Parents.IsEmpty()) {
        SetupLocation(Parents[0]);
    }
}

void UMinimapRepresentationComponent::SetupLocation(USceneComponent *InParent) {
    float Height;
    float Radius;
    InParent->CalcBoundingCylinder(Radius, Height);
    FVector Location = FVector(0, 0, Height + 10);
    SetRelativeLocation(Location, false);
    SetupForUnitOwner();
}

void UMinimapRepresentationComponent::SetupForBuildingOwner() {
}

void UMinimapRepresentationComponent::SetupForHeroOwner() {
}

void UMinimapRepresentationComponent::SetupForUnitOwner() {
}
// void USceneComponent::SetupAttachment(USceneComponent* InParent, FName InSocketName)
// {
// 	SetupAttachment(InParent, InSocketName);
// 	// SetupLocation(InParent);
// }