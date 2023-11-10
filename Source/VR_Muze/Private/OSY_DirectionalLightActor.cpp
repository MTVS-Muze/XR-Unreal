// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_DirectionalLightActor.h"
#include "Runtime/Engine/Classes/Components/DirectionalLightComponent.h"


AOSY_DirectionalLightActor::AOSY_DirectionalLightActor()
{
	PrimaryActorTick.bCanEverTick = true;
		

	compDirectionLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("compDirectionLight"));

	RootComponent = compDirectionLight;

}

void AOSY_DirectionalLightActor::BeginPlay()
{
	Super::BeginPlay();
}	

void AOSY_DirectionalLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
