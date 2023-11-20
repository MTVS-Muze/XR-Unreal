// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ModeSelectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AModeSelectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AModeSelectGameModeBase();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UMainWidget>ModeSelectWidget;

	class UMainWidget* ModeSelectUI;

	UFUNCTION()
	void GetMemberInfo();

	UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;

	UPROPERTY()
	class UOSY_GameInstance* gi;

private:
	
};
