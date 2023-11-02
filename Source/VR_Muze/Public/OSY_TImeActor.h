// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSY_TImeActor.generated.h"

UCLASS()
class VR_MUZE_API AOSY_TImeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSY_TImeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category = MySettings)
	float CurrentTime;

	// �ð� ����
	UPROPERTY(EditAnywhere,Category = MySettings)
	bool bShouldTick = false;

};
