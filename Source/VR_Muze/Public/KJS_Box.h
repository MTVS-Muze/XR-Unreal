// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJS_Box.generated.h"

UCLASS()
class VR_MUZE_API AKJS_Box : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKJS_Box();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Base")
	class UStaticMeshComponent* BoxOutside;

	UPROPERTY(EditAnywhere, Category = "Base")
	class UStaticMeshComponent* BoxInside;

	//UPROPERTY(EditAnywhere, Category = "Base")
	//class UBoxComponent* Boxcomp;

};
