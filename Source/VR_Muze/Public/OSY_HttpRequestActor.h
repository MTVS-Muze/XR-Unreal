// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/HttpFwd.h"
#include "OSY_JsonParseLibrary.h"
#include "OSY_HttpRequestActor.generated.h"

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

	void OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION()
	void PostRequest(const FString url);

	void OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);

	// 서버 주소
	UPROPERTY()
	FString sourceURL;

	// GameInstance
	class UOSY_GameInstance* MyGameInstance;

	UPROPERTY()
	class AOSY_CreativeGameModeBase* gm;

	// 파일 세이브하기
	void SaveJson(const FString jsonData);

	void ResetTime();

	float currenTime = 0;
	
};
