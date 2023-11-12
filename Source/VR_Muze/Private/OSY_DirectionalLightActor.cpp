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

void AOSY_DirectionalLightActor::ActiveLight(const FVector& FactoryLoc, bool isActivation)
{
	/*if (isActivation)
	{
		// 스네어 노드의 위치 설정 및 표시
		StartLocation = FactoryLoc;
		SetActorLocation(StartLocation);
		compMesh->SetVisibility(true);
		compBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CurrentLerpTime = 0;
		////UE_LOG(LogTemp, Warning, TEXT("make ----------------- %s"), *GetName());
		isHidden = false;
	}
	else
	{
		compMesh->SetVisibility(false);
		compBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		isHidden = true;
	}
	*/
}
