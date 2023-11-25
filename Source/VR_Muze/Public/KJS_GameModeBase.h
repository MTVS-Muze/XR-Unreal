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

public:
    TArray<FAllLevelData> AllLevelArray;

protected:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void BeginPlay() override;

public:
	UPROPERTY()
	class UOSY_GameInstance* gi;

    

public:
    class AMyCharacter* MyCharacter;

    UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;

    UFUNCTION()
    void SendReq();



};
