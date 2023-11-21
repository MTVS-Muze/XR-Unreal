// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OSY_CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AOSY_CustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOSY_CustomGameMode();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UCharacterCustomizeWidget>CustomWidget;
	class UCharacterCustomizeWidget* CustomUI;

	UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;

	UPROPERTY()
	class UOSY_GameInstance* gi;
	
};
