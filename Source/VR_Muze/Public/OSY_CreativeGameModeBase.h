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
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Scale;
};
UCLASS()
class VR_MUZE_API AOSY_CreativeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOSY_CreativeGameModeBase();
	virtual void BeginPlay() override;


private:
	class UDataTable* LevelInfoTable;


public:
	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_PropWidget> httpWidget;
	
	class UOSY_PropWidget* httpUI;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_SequenceWidget> SequenceWidget;
	
	class UOSY_SequenceWidget* SequnceUI;

	

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class USoundBase* superShy;


	UFUNCTION()
	void SetMaxTimeFromSong();

	

};
