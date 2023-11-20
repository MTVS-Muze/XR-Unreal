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
	//모듈을 생성하고 request 인스턴스를 생성한다.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	RequestedURL = url;

	// 요청하기 위한 정보를 설정한다.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetHeader(TEXT("Authorization"), BearerToken);
	if (url == gi->MemberInfourl)
	{

		req->OnProcessRequestComplete().BindUObject(this,&AOSY_HttpRequestActor::OnRecivedMemberData);
		UE_LOG(LogTemp, Warning, TEXT("Yogiha?"))

		
	}
	else if (url == gi->Playergeturl)
	{
		req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnReceivedPlayerData);
	}
	else if (url == gi->getlevelurl)
	{
		req->OnProcessRequestComplete().BindUObject(this, &AOSY_HttpRequestActor::OnReceivedlevelData);
	}
	req->ProcessRequest();

}
// 맴버 정보를 받아온다
void AOSY_HttpRequestActor::OnRecivedMemberData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("Received Data!"));

	if (bConnectedSuccessfully)
	{
		FString res = Response->GetContentAsString();
		FString parsedData = UOSY_JsonParseLibrary::PlayerJsonParse(res);

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

void AOSY_HttpRequestActor::OnReceivedPlayerData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("Received Data!"));

	if (bConnectedSuccessfully)
	{
		FString res = Response->GetContentAsString();
		FString parsedData = UOSY_JsonParseLibrary::PlayerJsonParse(res);

		if (gi != nullptr)
		{
			gi->parsePlayerData = parsedData;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
		
	}
}

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

	JsonObject->SetStringField("title", title);
	JsonObject->SetStringField("song", song);
	JsonObject->SetStringField("singer", singer);
	JsonObject->SetStringField("info", info);
	JsonObject->SetStringField("data", JsonString);

	/*
	TArray<TSharedPtr<FJsonValue>> SpawnInfosArray;

	for (const FActorSpawnInfo3& SpawnInfo : PendingSpawns)
	{
		TSharedPtr<FJsonObject> SpawnInfoObj = MakeShared<FJsonObject>();

		SpawnInfoObj->SetStringField("Location", FString::Printf(TEXT("(%f, %f, %f)"), SpawnInfo.Location.X, SpawnInfo.Location.Y, SpawnInfo.Location.Z));
		SpawnInfoObj->SetStringField("Rotation", FString::Printf(TEXT("(%f, %f, %f)"), SpawnInfo.Rotation.Pitch, SpawnInfo.Rotation.Yaw, SpawnInfo.Rotation.Roll));
		SpawnInfoObj->SetStringField("Scale", FString::Printf(TEXT("(%f, %f, %f)"), SpawnInfo.Scale.X, SpawnInfo.Scale.Y, SpawnInfo.Scale.Z));
		SpawnInfoObj->SetStringField("ActorClass", SpawnInfo.ActorClass->GetName());
		SpawnInfoObj->SetStringField("SpawnTime", FString::Printf(TEXT("%f"), SpawnInfo.SpawnTime));

		TSharedRef<FJsonValueObject> SpawnInfoValue = MakeShared<FJsonValueObject>(SpawnInfoObj);
		SpawnInfosArray.Add(SpawnInfoValue);
	}
	FString SpawnInfosArrayString;
	TSharedRef<TJsonWriter<>> ArrayWriter = TJsonWriterFactory<>::Create(&SpawnInfosArrayString);
	FJsonSerializer::Serialize(SpawnInfosArray, ArrayWriter);

	JsonObject->SetStringField("data", SpawnInfosArrayString); // Add the SpawnInfos array to the JsonObject with the key "data"

	*/
	FString OutputString;
	TSharedRef<TJsonWriter<>> ObjectWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), ObjectWriter);

	UE_LOG(LogTemp, Warning, TEXT("BearerToken: %s"), *BearerToken);

	// 요청 설정
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
// 		FString receivedData = Response->GetContentAsString();
// 		FString SavePath = FPaths::ProjectContentDir() + TEXT("SavedData.csv");


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

					// 액터 생성 정보를 구조체에 저장하고, 이를 리스트에 추가합니다.
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

