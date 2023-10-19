// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OSY_PropWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_PropWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_BoxSpawn;

	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> proptest;

	//UPROPERTY(VisibleAnywhere)
	//class AKJS_TestSpawnActor* Cube;


public:
	UFUNCTION()
	void SpawnBox();

	
};
