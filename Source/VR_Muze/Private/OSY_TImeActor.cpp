// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_TImeActor.h"

// Sets default values
AOSY_TImeActor::AOSY_TImeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSY_TImeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSY_TImeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldTick)
	{
		CurrentTime += DeltaTime;
	}

}

