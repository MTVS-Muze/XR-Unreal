// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "KJS_GameModeBase.h"
#include "KJS_MultiGameModeBase.generated.h"

struct FLevelInfo3
{
	FVector Location;
	FRotator Rotation;
	FVector Scale;
	UClass* ActorClass;
	float SpawnTime;
	float LifeSpan;
};

UCLASS()
class VR_MUZE_API AKJS_MultiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;

public:
	AKJS_MultiGameModeBase();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	APlayerStart* SpawnPlayerStart(FVector Location, FRotator Rotation, FString Tag);

	TArray<FAllLevelData> AllLevelArray;
	
	UPROPERTY()
	class UOSY_GameInstance* gi;

	UFUNCTION()
    void OnLevelSequenceFinished();

	UFUNCTION()
	void StartLevelSequence();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = NetworkFunction)
	void ServerStartLevelSequence();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = NetworkFunction)
	void MulticastStartLevelSequence();

	UFUNCTION()
    void SendReq();

	 UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;

	UFUNCTION()
	void LoadJsonData();

	UFUNCTION()
	void Play();

	TArray<FVector> Locations;
	TArray<FRotator> Rotations;
	TArray<FVector> Scales;
	TArray<FString> ActorClasses;
	TArray<float> SpawnTimes;
	TArray<float> LifeSpans;
	TArray<FLevelInfo3> PendingSpawns;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySequence)
	float CurrentTime;

	int32 currentIndex = 0;

	UFUNCTION()
	void Request();

private:
	TArray<APlayerStart*> UsedPlayerStarts;

	int32 callNumber = 1;

	
};
