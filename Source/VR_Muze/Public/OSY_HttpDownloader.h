// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "OSY_HttpDownloader.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_HttpDownloader : public UObject
{
	GENERATED_BODY()

public:
	UOSY_HttpDownloader();

	UFUNCTION(BlueprintCallable, DisplayName = "ExecuteDownload", Category = "HttpDownloader")
	void ExecuteDownload(FString SourceURL, FString Path, FString Name);


private:
	

private:
	// Ex: http://www.example.com/file.mp3

	// Ex: /Folder/Packs/
	UPROPERTY()
	FString path;
	// Ex: MyVideo.mp4
	UPROPERTY()
	FString name;
	

private:
	UFUNCTION()
	void SendRequest(const FString url);

	void OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// 서버 주소
	UPROPERTY()
	FString sourceURL;
		
};
