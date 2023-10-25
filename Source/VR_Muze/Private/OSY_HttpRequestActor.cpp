// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_HttpRequestActor.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "OSY_CSVParseLibrary.h"

// Sets default values
AOSY_HttpRequestActor::AOSY_HttpRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSY_HttpRequestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSY_HttpRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AOSY_HttpRequestActor::SendRequest(const FString url)
{
	//����� �����ϰ� request �ν��Ͻ��� �����Ѵ�.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�ϱ� ���� ������ �����Ѵ�.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("text/csv"));
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnReceivedData);
	req->ProcessRequest();

}

void AOSY_HttpRequestActor::OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("Success"));
		FString CSVData = Response->GetContentAsString();
		
		UE_LOG(LogTemp,Warning,TEXT("%s"),*CSVData);

		// CSV �����͸� �Ľ��մϴ�.
		TArray<FString> ParsedData = UOSY_CSVParseLibrary::ParseCSVFile(CSVData);

		TArray<FString> CSVLines;
		CSVData.ParseIntoArray(CSVLines, TEXT("\n"), true);

		TArray<FString> CSVColumns;
		for (const FString& Line : CSVLines)
		{
			CSVColumns.Empty();
			Line.ParseIntoArray(CSVColumns, TEXT(","), false);  // �� ���� ���� ����

			// ���� CSVColumns �迭�� �ش� ���� �����Ͱ� ������ ����˴ϴ�.
			// �ʿ信 ���� ������ ó���� �߰��Ͻʽÿ�.
			// ���� ���, CSVColumns �迭�� ����Ͽ� ���ϴ� ������� �����͸� ó���ϰų� ������ ������ �°� ��ȯ�� �� �ֽ��ϴ�.
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed..."));

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
	
	TArray<TMap<FString, FString>> levelData;
	levelData.Add(level1);

	FString MyCSVData = UOSY_CSVParseLibrary::MakeCSV(levelData);
	//gm->SetLogText(MyJsonData);

	// ��û ����
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("text/csv"));
	req->SetContentAsString(MyCSVData);
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnPostData);
	req->ProcessRequest();
}

void AOSY_HttpRequestActor::OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString receivedData = Response->GetContentAsString();
		UE_LOG(LogTemp,Warning,TEXT("Success"));
		//gm->SetLogText(receivedData);
	}
	else
	{

		// ��û ���� ���� Ȯ�� 
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
		// ���� �ڵ� Ȯ��
		int32 responseCode = Response->GetResponseCode();
		UE_LOG(LogTemp,Warning,TEXT("Recode : %s"),responseCode);
			//gm->SetLogText(FString::Printf(TEXT("Recode : %d"), responseCode));
	}
}

