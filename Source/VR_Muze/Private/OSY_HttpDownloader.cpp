// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_HttpDownloader.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "OSY_CSVParseLibrary.h"

UOSY_HttpDownloader::UOSY_HttpDownloader()
{
	//HttpModule = &FHttpModule::Get();
}

void UOSY_HttpDownloader::ExecuteDownload(FString SourceURL, FString Path, FString Name)
{
	sourceURL= SourceURL;
	path = Path;
	name = Name;
}

void UOSY_HttpDownloader::SendRequest(const FString url)
{
	//모듈을 생성하고 request 인스턴스를 생성한다.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 요청하기 위한 정보를 설정한다.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"),TEXT("text/csv"));
	req->OnProcessRequestComplete().BindUObject(this,&UOSY_HttpDownloader::OnReceivedData);
	req->ProcessRequest();
}

void UOSY_HttpDownloader::OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp,Warning,TEXT("Success"));
		FString CSVData = Response->GetContentAsString();

		// CSV 데이터를 파싱합니다.
		TArray<FString> ParsedData = UOSY_CSVParseLibrary::ParseCSVFile(CSVData);

		// ParsedData를 원하는 방식으로 처리하거나 출력할 수 있습니다.
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed..."));

	}

}
