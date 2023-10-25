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
	//����� �����ϰ� request �ν��Ͻ��� �����Ѵ�.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�ϱ� ���� ������ �����Ѵ�.
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

		// CSV �����͸� �Ľ��մϴ�.
		TArray<FString> ParsedData = UOSY_CSVParseLibrary::ParseCSVFile(CSVData);

		// ParsedData�� ���ϴ� ������� ó���ϰų� ����� �� �ֽ��ϴ�.
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed..."));

	}

}
