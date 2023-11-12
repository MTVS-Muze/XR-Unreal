// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSY_LightPool.generated.h"

UCLASS()
class VR_MUZE_API AOSY_LightPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSY_LightPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
#pragma region PoolSize
	UPROPERTY()
	int DPS = 1;
	UPROPERTY()
	int SPS = 4;
	UPROPERTY()
	int PPS = 4;
#pragma endregion

	// ������Ʈ Ǯ�� ������ �迭 �̸鼭 InActive��带 ��� �ְ���
	TArray<AActor*> ActorPool;

	// Active��带 ���� ����Ʈ��.
	TArray<AActor*> ActivePool;

	UPROPERTY(EditAnywhere, Category="MySettings")
    TSubclassOf<class AOSY_DirectionalLightActor> DirectionalFac;

	UPROPERTY(EditAnywhere, Category="MySettings")
    TSubclassOf<class AOSY_SpotLightActor> SpotFac;

	UPROPERTY(EditAnywhere, Category="MySettings")
    TSubclassOf<class AOSY_PointLightActor> PointFac;











};
