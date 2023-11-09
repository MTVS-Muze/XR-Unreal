// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJS_BoxSofa.generated.h"

UCLASS()
class VR_MUZE_API AKJS_BoxSofa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKJS_BoxSofa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "StaticMeshList")
	TArray<UStaticMesh*> StaticMeshOptions;

	UPROPERTY(EditAnywhere, Category = "Base")
	class UStaticMeshComponent* SelectedStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Base")
	class USkeletalMeshComponent* SelectedSkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Base")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = "Base")
	class UMediaLobbyWidget* ViewWidget;
	
	UFUNCTION()
	void SetMesh();

};
