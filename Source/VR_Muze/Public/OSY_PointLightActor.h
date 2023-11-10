// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OSY_LightBaseActor.h"
#include "OSY_PointLightActor.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AOSY_PointLightActor : public AOSY_LightBaseActor
{
	GENERATED_BODY()

	public:
	// Sets default values for this pawn's properties
	AOSY_PointLightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category= MySettings)
	class UPointLightComponent* compPointLight;
	
	
};
