// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AKJS_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	UFUNCTION()
	void SetVRMode();

};
