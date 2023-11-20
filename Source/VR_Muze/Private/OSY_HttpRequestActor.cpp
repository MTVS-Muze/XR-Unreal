// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_HttpRequestActor.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "OSY_CSVParseLibrary.h"
#include "OSY_GameInstance.h"
#include "OSY_CreativeGameModeBase.h"
#include "OSY_JsonParseLibrary.h"
#include "OSY_PropWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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

	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	Token = gi->Token;
	BearerToken = "Bearer " + Token;
	
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

	RequestedURL = url;

	// ��û�ϱ� ���� ������ �����Ѵ�.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetHeader(TEXT("Authorization"), BearerToken);
	if (url == gi->MemberInfourl)
	{

		req->OnProcessRequestComplete().BindUObject(this,&AOSY_HttpRequestActor::OnRecivedMemberData);
		UE_LOG(LogTemp, Warning, TEXT("Yogiha?"))

		
	}
	else if (url == gi->CustomURL)
	{
		req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnReceivedCustomData);
	}
	else if (url == gi->getlevelurl)
	{
		req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnReceivedlevelData);
	}
	req->ProcessRequest();

}
// �ɹ� ������ �޾ƿ´�
void AOSY_HttpRequestActor::OnRecivedMemberData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("Received Data!"));

	if (bConnectedSuccessfully)
	{
		FString res = Response->GetContentAsString();
		FString parsedData = UOSY_JsonParseLibrary::PlayerInfoJsonParse(res);

		if (gi != nullptr)
		{
			TArray<FString> parsedDataArray;
			parsedData.ParseIntoArray(parsedDataArray, TEXT(":"), true);

			
				gi->id = FCString::Atoi(*parsedDataArray[0]);
				gi->name = parsedDataArray[1];
				gi->sub = parsedDataArray[2];
				gi->profileImage = parsedDataArray[3]+parsedDataArray[4];
				gi->platform = parsedDataArray[5];
				gi->role = parsedDataArray[6];
				gi->email = parsedDataArray[7];
		

			gi->parsePlayerData = parsedData;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));

	}
}
// Ŀ�� ������ �޾ƿ´�
void AOSY_HttpRequestActor::OnReceivedCustomData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("Received Data!"));

	if (bConnectedSuccessfully)
	{
		FString res = Response->GetContentAsString();
		FString parsedData = UOSY_JsonParseLibrary::PlayerCustomJsonParse(res);

		if (gi != nullptr)
		{
			TArray<FString> parsedDataArray;
			parsedData.ParseIntoArray(parsedDataArray, TEXT(":"), true);


			gi->color = FCString::Atoi(*parsedDataArray[0]);
			gi->hat = FCString::Atoi(*parsedDataArray[1]);
			gi->glass = FCString::Atoi(*parsedDataArray[2]);
			gi->tie = FCString::Atoi(*parsedDataArray[3]);

			gi->parseCustomData = parsedData;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
		
	}
}
// �� ������ �޾ƿ´�
void AOSY_HttpRequestActor::OnReceivedlevelData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("Received Data!"));

	if (bConnectedSuccessfully)
	{
		FString res = Response->GetContentAsString();
		FString parsedData = UOSY_JsonParseLibrary::LevelJsonParse(res);

		if (gi != nullptr)
		{
			gi->parseLevelData = parsedData;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));

	}
}

void AOSY_HttpRequestActor::PostRequest(const FString url, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	//

	if (url == gi->PostMyMap)
	{
		JsonObject->SetStringField("title", gi->title);
		JsonObject->SetStringField("song", gi->song);
		JsonObject->SetStringField("singer", gi->singer);
		JsonObject->SetStringField("info", gi->info);
		JsonObject->SetStringField("data", JsonString);


	}
	else if (url == gi->CustomURL)
	{
		JsonObject->SetNumberField("color", gi->color);
		JsonObject->SetNumberField("color", gi->hat);
		JsonObject->SetNumberField("color", gi->glass);
		JsonObject->SetNumberField("color", gi->tie);
	}

	FString OutputString;
	TSharedRef<TJsonWriter<>> ObjectWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), ObjectWriter);

	UE_LOG(LogTemp, Warning, TEXT("BearerToken: %s"), *BearerToken);

	// ��û ����
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetHeader(TEXT("Authorization"), BearerToken);
	req->SetContentAsString(OutputString);
	req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnPostData);
	req->ProcessRequest();
}

void AOSY_HttpRequestActor::OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp,Warning,TEXT("Success"));

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

void AOSY_HttpRequestActor::SaveJson(const FString jsonData)
{
	// ������ �̸��� ������ ������ �ش� ������ �����.
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

void AOSY_HttpRequestActor::LoadJsonData()
{
	FString LoadPath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");

	FString JsonString;
	if (FFileHelper::LoadFileToString(JsonString, *LoadPath))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			if (JsonObject->HasField(TEXT("Locations")) && JsonObject->HasField(TEXT("Rotations")) && JsonObject->HasField(TEXT("Scales")) && JsonObject->HasField(TEXT("ActorClasses")) && JsonObject->HasField(TEXT("SpawnTime")))
			{
				TArray<TSharedPtr<FJsonValue>> LocationsArray = JsonObject->GetArrayField(TEXT("Locations"));
				TArray<TSharedPtr<FJsonValue>> RotationsArray = JsonObject->GetArrayField(TEXT("Rotations"));
				TArray<TSharedPtr<FJsonValue>> ScalesArray = JsonObject->GetArrayField(TEXT("Scales"));
				TArray<TSharedPtr<FJsonValue>> ActorClassesArray = JsonObject->GetArrayField(TEXT("ActorClasses"));
				TArray<TSharedPtr<FJsonValue>> SpawnTimeArray = JsonObject->GetArrayField(TEXT("SpawnTime"));

				for (int i = 0; i < LocationsArray.Num(); i++)
				{
					TSharedPtr<FJsonObject> LocationObj = LocationsArray[i]->AsObject();
					TSharedPtr<FJsonObject> RotationObj = RotationsArray[i]->AsObject();
					TSharedPtr<FJsonObject> ScaleObj = ScalesArray[i]->AsObject();

					FVector LoadedLocation(LocationObj->GetNumberField(TEXT("X")), LocationObj->GetNumberField(TEXT("Y")), LocationObj->GetNumberField(TEXT("Z")));
					FRotator LoadedRotation(RotationObj->GetNumberField(TEXT("Pitch")), RotationObj->GetNumberField(TEXT("Yaw")), RotationObj->GetNumberField(TEXT("Roll")));
					FVector LoadedScale(ScaleObj->GetNumberField(TEXT("X")), ScaleObj->GetNumberField(TEXT("Y")), ScaleObj->GetNumberField(TEXT("Z")));

					FString ActorClassName = ActorClassesArray[i]->AsString();
					UClass* ActorClass = LoadObject<UClass>(nullptr, *ActorClassName);

					float SavedTime = SpawnTimeArray[i]->AsNumber();

					// ���� ���� ������ ����ü�� �����ϰ�, �̸� ����Ʈ�� �߰��մϴ�.
					FActorSpawnInfo3 SpawnInfo;
					SpawnInfo.Location = LoadedLocation;
					SpawnInfo.Rotation = LoadedRotation;
					SpawnInfo.Scale = LoadedScale;
					SpawnInfo.ActorClass = ActorClass;
					SpawnInfo.SpawnTime = SavedTime;

					PendingSpawns.Add(SpawnInfo);
				}
			}
		}
	}

	//PostRequest(url2);
}

void AOSY_HttpRequestActor::ResetTime()
{
	currenTime = 0;
}

void AOSY_HttpRequestActor::ParseDataForURL1(const FString& ResponseData)
{

}

void AOSY_HttpRequestActor::ParseDataForURL2(const FString& ResponseData)
{

}

