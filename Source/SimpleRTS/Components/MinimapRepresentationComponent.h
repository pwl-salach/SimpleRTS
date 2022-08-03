// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MinimapRepresentationComponent.generated.h"


// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS()
class SIMPLERTS_API UMinimapRepresentationComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMinimapRepresentationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// void SetupAttachment(USceneComponent* InParent, FName InSocketName = NAME_None);
	virtual void OnAttachmentChanged() override;

private:
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	class UStaticMesh* MinimapSprite;


	void SetupForBuildingOwner();
	void SetupForHeroOwner();
	void SetupForUnitOwner();
	void SetupLocation(class USceneComponent* InParent);
		
};
