// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 1200;
	RotateSpeed = 200;

	MinZoom = 300;
	MaxZoom = 4500;
	ZoomingSpeed = 100;
	DefaultZoom = 3000;
	CurrentZoom = DefaultZoom;
	ZoomChange = 0;
	ScreenEdgeMovementMargin = 5;

	RotateEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	SpringArm->TargetArmLength = CurrentZoom;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// PlayerInputComponent->BindAxis("ScreenXBorder", this, &ACameraPawn::CalculateStraightMove);
	PlayerInputComponent->BindAxis("RotateTrigger", this, &ACameraPawn::HandleRotateTrigger);
	PlayerInputComponent->BindAxis("MouseRotate", this, &ACameraPawn::CalculateRotationInput);
	PlayerInputComponent->BindAxis("ScrollZoom", this, &ACameraPawn::CalculateZoomChange);
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateScreenEdgesMovement();
	RotateCamera();
	MoveCamera();
	HandleCameraZoom();
}

void ACameraPawn::CalculateStraightMove(float Value) 
{

	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, MoveDirection.Y, 0);
}

void ACameraPawn::CalculateSideMove(float Value) 
{
	MoveDirection = FVector(MoveDirection.X, Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0);
}

void ACameraPawn::CalculateRotationInput(float Value) 
{
	if(RotateEnabled){
		float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
		FRotator Rotation = FRotator(0, RotateAmount, 0);
		RotationDirection = FQuat(Rotation);
	} else {
		FRotator Rotation = FRotator(0, 0, 0);
		RotationDirection = FQuat(Rotation);
	}
}

void ACameraPawn::CalculateScreenEdgesMovement() 
{
	if(RotateEnabled) return;
	
	UGameViewportClient* GameViewport = GEngine->GameViewport;
	if(!GameViewport) return;

	FVector2D MousePosition;
	if (GameViewport->IsFocused(GameViewport->Viewport) && GameViewport->GetMousePosition(MousePosition))
    {
		FVector2D ScreenSize;

		GameViewport->GetViewportSize(ScreenSize);
		if (ScreenEdgeMovementMargin > MousePosition.Y){
			// forward
			CalculateStraightMove(1.f);
		} else if(ScreenSize.Y - ScreenEdgeMovementMargin < MousePosition.Y){
			//backward
			CalculateStraightMove(-1.f);
		} else {
			CalculateStraightMove(0.f);
		}

		if(ScreenSize.X - ScreenEdgeMovementMargin < MousePosition.X){
			//right
			CalculateSideMove(1.f);
		} else if (ScreenEdgeMovementMargin > MousePosition.X){
			// left
			CalculateSideMove(-1.f);
		} else {
			CalculateSideMove(0.f);
		}
	}
}

void ACameraPawn::MoveCamera() 
{
	AddActorLocalOffset(MoveDirection, false);
}

void ACameraPawn::RotateCamera() 
{
	AddActorLocalRotation(RotationDirection, false);
}

void ACameraPawn::HandleRotateTrigger(float Value) 
{
	RotateEnabled = Value > 0;
}

void ACameraPawn::HandleCameraZoom() 
{
	// Zooming in
	int32 TmpZoom = CurrentZoom - ZoomChange;
	if(MinZoom > TmpZoom)
		CurrentZoom = MinZoom;
	else if (MaxZoom < TmpZoom)
		CurrentZoom = MaxZoom;
	else
		CurrentZoom = TmpZoom;
	SpringArm->TargetArmLength = CurrentZoom;
}

void ACameraPawn::CalculateZoomChange(float Value) 
{
	ZoomChange = (int32)(Value * ZoomingSpeed);
}


