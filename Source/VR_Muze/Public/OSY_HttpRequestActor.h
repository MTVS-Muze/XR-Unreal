// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/HttpFwd.h"
#include "OSY_JsonParseLibrary.h"
#include "OSY_HttpRequestActor.generated.h"


struct FActorSpawnInfo3
{
	FVector Location;
	FRotator Rotation;
	FVector Scale;
	UClass* ActorClass;
	float SpawnTime;
};
UCLASS()
class VR_MUZE_API AOSY_HttpRequestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSY_HttpRequestActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Ex: http://www.example.com/file.mp3

	
public:
	UFUNCTION()
	void SendRequest(const FString url);

	// 나의 정보를 줘
	void OnRecivedMemberData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	// 커스텀 줘
	void OnReceivedCustomData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	// 레벨 전부다 줘
	void OnReceivedAllLevel(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	// 내가 만든 레벨 다줘
	void OnReceivedAllMyLevel(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	// 내가 만든 레벨 하나만 줘
	void OnReceivedlevelData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION()
	void PostRequest(const FString url, const FString& JsonString);

	void OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);

	// 서버 주소
	UPROPERTY()
	FString sourceURL;

	// GameInstance
	class UOSY_GameInstance* MyGameInstance;

	UPROPERTY()
	class AOSY_CreativeGameModeBase* OCgm;

	UPROPERTY()
	class AKJS_GameModeBase* KVgm;

	UPROPERTY()
	class AModeSelectGameModeBase* MSgm;

	UPROPERTY()
	class AKJS_CustomizeGameModeBase* KCgm;

	UPROPERTY()
	class AKJS_MultiGameModeBase* Multigm;

	// 파일 세이브하기
	void SaveJson(const FString jsonData);

	void LoadJsonData();

	void ResetTime();

	float currenTime = 0;

	UPROPERTY()
	FString url2 ="http://192.168.0.189:8080/map/create";
	
	TArray<FActorSpawnInfo3> PendingSpawns;

	FString Token;
	
	FString title;
	FString song;
	FString singer;
	FString info;
	FString data;
	

	UPROPERTY()
	class UOSY_GameInstance* gi;

	UPROPERTY()
	FString BearerToken;

	FString RequestedURL;

	void ParseDataForURL1(const FString& ResponseData);
	void ParseDataForURL2(const FString& ResponseData);

	void GetImage(const FString url);
	void OnGetImageData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);

	
};
