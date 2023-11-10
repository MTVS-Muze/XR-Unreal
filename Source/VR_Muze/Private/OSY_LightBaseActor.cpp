// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LightBaseActor.h"

// Sets default values
AOSY_LightBaseActor::AOSY_LightBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSY_LightBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSY_LightBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

