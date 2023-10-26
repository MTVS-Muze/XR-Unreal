// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSY_NiagaraSpawner.generated.h"

UCLASS()
class VR_MUZE_API AOSY_NiagaraSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSY_NiagaraSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// GameInstance
	class UOSY_GameInstance* MyGameInstance;

	//UPROPERTY(EditAnywhere, Category = "MySettings")
	


	float currentTime =0;

	// 프랍위젯에서 버튼이 누르면 실행될 함수
	void spawnStart();

	// 오브젝트 풀 사이즈
	int PoolSize;

};
