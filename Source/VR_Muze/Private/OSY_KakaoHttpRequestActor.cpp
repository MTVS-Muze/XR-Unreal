// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_KakaoHttpRequestActor.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "OSY_JsonParseLibrary.h"

// Sets default values
AOSY_KakaoHttpRequestActor::AOSY_KakaoHttpRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSY_KakaoHttpRequestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSY_KakaoHttpRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOSY_KakaoHttpRequestActor::SendRequest(const FString url)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_KakaoHttpRequestActor::OnReceivedData);
	req->ProcessRequest();
}

void AOSY_KakaoHttpRequestActor::OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{

		FString res = Response->GetContentAsString();


		UOSY_JsonParseLibrary JsonParser; // 클래스 인스턴스를 직접 생성

		TSharedPtr<FJsonObject> ParsedData = JsonParser.ParseJSON(res);

		if (ParsedData.IsValid())
		{
			// JSON 데이터를 파싱한 후 필요한 값을 추출합니다.
			FString Token = ParsedData->GetStringField("Token");

			UE_LOG(LogTemp, Warning, TEXT("MemberId: %s"), *Token);

			// 나머지 코드...
		}
		UE_LOG(LogTemp, Warning, TEXT("Successed.."));
		UE_LOG(LogTemp, Warning, TEXT("% s"), *res);

	}

	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Failed.."));
	}
}

void AOSY_KakaoHttpRequestActor::PostRequest(const FString url)
{
	TMap<FString, FString> level1;
	level1.Add("name", "SEYOUNG");
	level1.Add("spawnTime", "2");
	level1.Add("dieTime", "10");
	level1.Add("locationX", "0");
	level1.Add("locationY", "0");
	level1.Add("locationZ", "0");
	level1.Add("scale", "2");
	level1.Add("texture", "1");


	FString MyJsonData = UOSY_JsonParseLibrary::MakeJson(level1);
	//gm->SetLogText(MyJsonData);

	// 요청 설정
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(MyJsonData);
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_KakaoHttpRequestActor::OnPostData);
	req->ProcessRequest();
}

void AOSY_KakaoHttpRequestActor::OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString receivedData = Response->GetContentAsString();
		FString SavePath = FPaths::ProjectContentDir() + TEXT("SavedData.csv");


		UE_LOG(LogTemp, Warning, TEXT("Success"));

		//gm->SetLogText(receivedData);
	}
	else
	{

		// 요청 전송 상태 확인 
		EHttpRequestStatus::Type status = Request->GetStatus();
		switch (status)
		{
		case EHttpRequestStatus::NotStarted:
			break;
		case EHttpRequestStatus::Processing:
			break;
		case EHttpRequestStatus::Failed:
			break;
		case EHttpRequestStatus::Failed_ConnectionError:
			break;
		case EHttpRequestStatus::Succeeded:
			break;
		default:
			break;
		}
		// 응답 코드 확인
		int32 responseCode = Response->GetResponseCode();
		UE_LOG(LogTemp, Warning, TEXT("Recode : %s"), responseCode);
		//gm->SetLogText(FString::Printf(TEXT("Recode : %d"), responseCode));
	}
}

