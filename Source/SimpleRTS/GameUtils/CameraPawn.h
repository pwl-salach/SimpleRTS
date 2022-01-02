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

	// Do I need any blueprints related stuff?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int32 MoveSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int32 RotateSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int32 ZoomingSpeed;

	// Camera constrains
	int32 MinZoom;
	int32 MaxZoom;
	int32 MinHeightAboveLandscape;
	int32 MaxHeightAboveLandscape;
	int32 ScreenEdgeMovementMargin;

	int32 DefaultZoom;
	int32 CurrentZoom;
	
	// change realted variables
	FVector MoveDirection;
	bool RotateEnabled;
	FQuat RotationDirection;
	int32 ZoomChange;

	void CalculateScreenEdgesMovement();
	void CalculateStraightMove(float Value);
	void CalculateSideMove(float Value);
	void CalculateRotationInput(float Value);
	void HandleRotateTrigger(float Value);
	void HandleMovement();

	void CalculateZoomChange(float Value);
	void HandleZoom();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
