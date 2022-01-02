// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	MainTexture = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Texture"));
	MainTexture->SetupAttachment(CapsuleComponent);

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

