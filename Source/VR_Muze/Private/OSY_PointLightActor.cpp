// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PointLightActor.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"

AOSY_PointLightActor::AOSY_PointLightActor()
{
	PrimaryActorTick.bCanEverTick = true;

	compPointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("compDirectionLight"));

	RootComponent = compPointLight;

}

void AOSY_PointLightActor::BeginPlay()
{
	Super::BeginPlay();
}

void AOSY_PointLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
