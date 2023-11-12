// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OSY_StreetGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AOSY_StreetGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AOSY_StreetGameMode();
	virtual void BeginPlay();

public:
	UFUNCTION()
	void PlaySequence();
	
};
