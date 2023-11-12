// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LightPool.h"
#include "OSY_DirectionalLightActor.h"
#include "OSY_SpotLightActor.h"
#include "OSY_PointLightActor.h"

// Sets default values
AOSY_LightPool::AOSY_LightPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSY_LightPool::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < DPS; i++)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AOSY_DirectionalLightActor* DirectionalLight = GetWorld()->SpawnActor<AOSY_DirectionalLightActor>(DirectionalFac, param);

		//SnareNode->SetActorHiddenInGame(true);
		DirectionalLight->ActiveLight(FVector(), false);
		ActorPool.Add(DirectionalLight);
	}
	for (int32 i = 0; i < SPS; i++)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AOSY_SpotLightActor* SpotLight = GetWorld()->SpawnActor<AOSY_SpotLightActor>(SpotFac, param);

		//SnareNode->SetActorHiddenInGame(true);
		SpotLight->ActiveLight(FVector(), false);
		ActorPool.Add(SpotLight);
	}
	for (int32 i = 0; i < PPS; i++)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AOSY_PointLightActor* PointLight = GetWorld()->SpawnActor<AOSY_PointLightActor>(PointFac, param);

		//SnareNode->SetActorHiddenInGame(true);
		PointLight->ActiveLight(FVector(), false);
		ActorPool.Add(PointLight);
	}
	
}

// Called every frame
void AOSY_LightPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

