// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSY_MovieSceneSequenceActor.generated.h"

UCLASS()
class VR_MUZE_API AOSY_MovieSceneSequenceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSY_MovieSceneSequenceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CreateSequence();

	UFUNCTION()
	void PlaySequence();

	UPROPERTY(EditAnywhere)
    AActor* MyActor;

};
