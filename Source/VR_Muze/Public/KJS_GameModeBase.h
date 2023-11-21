// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJS_GameModeBase.generated.h"

USTRUCT()
struct FAllLevelData
{
    GENERATED_BODY()

    int32 Id;
    FString MemberName;
    FString Title;
    FString Song;
    FString Singer;
    FString Info;
    FString Data;
    FString CreatedDate;
};
UCLASS()
class VR_MUZE_API AKJS_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	
	
	UFUNCTION()
	void SetVRMode();
public:
	UFUNCTION()
	void PlaySequence();

    TArray<FAllLevelData> AllLevelArray;

};
