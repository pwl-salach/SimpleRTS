// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include "Components/CapsuleComponent.h"
#include "../Components/SelectableComponent.h"
#include "../Components/MinimapRepresentationComponent.h"


// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	MainTexture = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Texture"));
	MainTexture->SetupAttachment(CapsuleComponent);

	SelectableComponent = CreateDefaultSubobject<USelectableComponent>(TEXT("Selected Representation"));
	SelectableComponent->SetPriority(10);
	SelectableComponent->RegisterComponent();

	MinimapRepresentation = CreateDefaultSubobject<UMinimapRepresentationComponent>(TEXT("Minimap Representation"));
	MinimapRepresentation->SetupAttachment(CapsuleComponent);
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

