// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class SIMPLERTS_API ACameraPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// Camera related
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int32 MoveSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int32 RotateSpeed;

	// Camera constrains
	int32 MinZoom;
	int32 MaxZoom;
	int32 ZoomingSpeed;
	int32 CurrentZoom;
	int32 DefaultZoom;
	int32 ZoomChange;
	
	int32 ScreenEdgeMovementMargin;
	FVector MoveDirection;
	FQuat RotationDirection;

	bool RotateEnabled;

	void CalculateStraightMove(float Value);
	void CalculateSideMove(float Value);
	void MoveCamera();

	void HandleCameraZoom();
	void CalculateZoomChange(float Value);

	//Not used
	void CalculateRotationInput(float Value);
	void CalculateScreenEdgesMovement();

	void RotateCamera();

	void HandleRotateTrigger(float Value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
