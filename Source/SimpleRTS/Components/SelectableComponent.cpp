// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableComponent.h"
#include "Engine/Texture2D.h"

// Sets default values for this component's properties
USelectableComponent::USelectableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Mobile = false;
	Selected = false;
	Focused = false;
	Priority = 10;  // lowest which makes it selectable
	// ...
}


// Called when the game starts
void USelectableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USelectableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UTexture2D* USelectableComponent::GetAvatar() 
{
	return Avatar;
}

uint8 USelectableComponent::GetPriority() 
{
	return Priority;
}

void USelectableComponent::SetPriority(uint8 NewPriority) 
{
	Priority = NewPriority;
}

bool USelectableComponent::CanMove() 
{
	return Mobile;
}

