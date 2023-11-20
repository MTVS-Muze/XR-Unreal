// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

	UPROPERTY()
	USoundBase* Song;
	UPROPERTY()
	class UOSY_GameInstance* gi;

	

};
