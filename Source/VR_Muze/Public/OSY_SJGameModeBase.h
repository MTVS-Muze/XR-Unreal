// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OSY_SJGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AOSY_SJGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AOSY_SJGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime)override;

	UPROPERTY()
	class UOSY_GameInstance* gi;

	UPROPERTY()
	class AOSY_HttpRequestActor* HttpActor;


	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;

	
};
