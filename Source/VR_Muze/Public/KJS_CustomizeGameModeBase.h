// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJS_CustomizeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AKJS_CustomizeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	UPROPERTY()
	class UOSY_GameInstance* gi;

	UFUNCTION()
	void OnSequenceFinished();

	UFUNCTION()
	void SetImage(class UTexture2D* tex);

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_MyInfoWidget> MyInfoWidget;
	
	class UOSY_MyInfoWidget* MyInfoUI;

	
};
