// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_SpotLightActor.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"

AOSY_SpotLightActor::AOSY_SpotLightActor()
{
	PrimaryActorTick.bCanEverTick = true;


	compSpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("compDirectionLight"));

	RootComponent = compSpotLight;
}

void AOSY_SpotLightActor::BeginPlay()
{
	Super::BeginPlay();
}

void AOSY_SpotLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOSY_SpotLightActor::ActiveLight(const FVector& FactoryLoc, bool isActivation)
{

}
