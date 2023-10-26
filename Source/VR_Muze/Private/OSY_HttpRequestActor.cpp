// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_HttpRequestActor.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "OSY_CSVParseLibrary.h"
#include "OSY_GameInstance.h"
#include "OSY_CreativeGameModeBase.h"
#include "OSY_JsonParseLibrary.h"

// Sets default values
AOSY_HttpRequestActor::AOSY_HttpRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//MyGameInstance = Cast<UOSY_GameInstance>(GetGameInstance());

}

// Called when the game starts or when spawned
void AOSY_HttpRequestActor::BeginPlay()
{
	Super::BeginPlay();

	gm = GetWorld()->GetAuthGameMode<AOSY_CreativeGameModeBase>();


	
}

// Called every frame
void AOSY_HttpRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currenTime+= DeltaTime;
	

}


void AOSY_HttpRequestActor::SendRequest(const FString url)
{
	//모듈을 생성하고 request 인스턴스를 생성한다.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 요청하기 위한 정보를 설정한다.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnReceivedData);
	req->ProcessRequest();

}

void AOSY_HttpRequestActor::OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		
		FString res = Response->GetContentAsString();


		 UOSY_JsonParseLibrary JsonParser; // 클래스 인스턴스를 직접 생성

		TSharedPtr<FJsonObject> ParsedData = JsonParser.ParseJSON(res);

		if (ParsedData.IsValid())
		{
			// JSON 데이터를 파싱한 후 필요한 값을 추출합니다.
			int Id = ParsedData->GetIntegerField("id");
			FString MemberId = ParsedData->GetStringField("memberId");
			FString Title = ParsedData->GetStringField("title");
			FString Song = ParsedData->GetStringField("song");
			FString Data = ParsedData->GetStringField("data");
			FString CreatedDate = ParsedData->GetStringField("createdDate");

			UE_LOG(LogTemp, Warning, TEXT("Id: %d"), Id);
			UE_LOG(LogTemp, Warning, TEXT("MemberId: %s"), *MemberId);
			UE_LOG(LogTemp, Warning, TEXT("Title: %s"), *Title);
			UE_LOG(LogTemp, Warning, TEXT("Song: %s"), *Song);
			UE_LOG(LogTemp, Warning, TEXT("Data: %s"), *Data);
			UE_LOG(LogTemp, Warning, TEXT("CreatedDate: %s"), *CreatedDate);

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

void AOSY_HttpRequestActor::PostRequest(const FString url)
{
	TMap<FString,FString> level1;
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
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnPostData);
	req->ProcessRequest();
}

void AOSY_HttpRequestActor::OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString receivedData = Response->GetContentAsString();
		FString SavePath = FPaths::ProjectContentDir() + TEXT("SavedData.csv");


		UE_LOG(LogTemp,Warning,TEXT("Success"));

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
		UE_LOG(LogTemp,Warning,TEXT("Recode : %s"),responseCode);
			//gm->SetLogText(FString::Printf(TEXT("Recode : %d"), responseCode));
	}
}

void AOSY_HttpRequestActor::SaveJson(const FString jsonData)
{
	// 지정된 이름의 폴더가 없으면 해당 폴더를 만든다.
	FPlatformFileManager& fileManager = FPlatformFileManager::Get();
	IPlatformFile& platformFile = fileManager.GetPlatformFile();


	FString dirPath = FPaths::ProjectContentDir() + "/Jso00nData";
	if (!platformFile.DirectoryExists(*dirPath))
	{
		platformFile.CreateDirectory(*dirPath);
	}

	FString fullPath = dirPath + "MyJson.json";
	UE_LOG(LogTemp, Warning, TEXT("save Path :%s"), *fullPath);
	bool bIsSaved = FFileHelper::SaveStringToFile(jsonData, *fullPath);
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), bIsSaved ? *FString("Json Saved Successfully!!") : *FString("FAILED saving file->.."));
}

void AOSY_HttpRequestActor::ResetTime()
{
	currenTime = 0;
}

