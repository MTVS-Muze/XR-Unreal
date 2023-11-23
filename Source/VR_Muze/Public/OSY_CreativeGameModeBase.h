// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJS_GameModeBase.h"
#include "OSY_CreativeGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FActorTransformInfo
{
    GENERATED_BODY()

public:
	FVector Location;
	FRotator Rotation;
	FVector Scale;
	UClass* ActorClass;
	float SpawnTime;
	float LifeSpan;
	int text;
};
UCLASS()
class VR_MUZE_API AOSY_CreativeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOSY_CreativeGameModeBase();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime)override;


private:
	class UDataTable* LevelInfoTable;


public:
	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_PropWidget> httpWidget;
	
	class UOSY_PropWidget* httpUI;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_SequenceWidget> SequenceWidget;
	
	class UOSY_SequenceWidget* SequnceUI;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_OutLinerWidget> OutLinerWidget;
	
	class UOSY_OutLinerWidget* OutLinerUI;

	

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class USoundBase* superShy;


	UFUNCTION()
	void SetMaxTimeFromSong();

	
	TArray<FActorTransformInfo> postData;

	TArray<FAllLevelData> AllLevel;

	UPROPERTY()
	USoundBase* Song;
	UPROPERTY()
	class UOSY_GameInstance* gi;


	UPROPERTY()
	class AOSY_HttpRequestActor* HttpActor;

	UFUNCTION()
	void Request();

public:
	TArray<FVector> Locations;
	TArray<FRotator> Rotations;
	TArray<FVector> Scales;
	TArray<FString> ActorClasses;
	TArray<float> SpawnTimes;
	TArray<float> LifeSpans;

	FString PlaySong;
	

};
