// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUnit.h"

#include "../Components/MinimapRepresentationComponent.h"
#include "../Components/SelectableComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseUnit::ABaseUnit() {
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SelectableComponent = CreateDefaultSubobject<USelectableComponent>(TEXT("Selected Representation"));
    SelectableComponent->SetPriority(20);
    SelectableComponent->RegisterComponent();

    MinimapRepresentation = CreateDefaultSubobject<UMinimapRepresentationComponent>(TEXT("Minimap Representation"));
    MinimapRepresentation->SetupAttachment(RootComponent);

    Speed = 50;
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    // FVector Delta = GetActorLocation() - TargetLocation;
    // float DistanceToGoal = Delta.Size();
    // if (DistanceToGoal > 75) {
    // UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
    // }
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseUnit::MoveToLocation(FVector NewTargetLocation) {
    TargetLocation = TranslateToCapsuleCenterLocation(NewTargetLocation);
    SetActorLocation(TargetLocation);
}

FVector ABaseUnit::TranslateToCapsuleCenterLocation(FVector Location) {
    float HalfHeight;
    float Radius;
    GetCapsuleComponent()->CalcBoundingCylinder(Radius, HalfHeight);
    return FVector(Location.X, Location.Y, Location.Z + HalfHeight);
}
