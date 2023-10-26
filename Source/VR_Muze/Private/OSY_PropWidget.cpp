// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PropWidget.h"
#include "Components/Button.h"
#include "KJS_TestSpawnActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "LevelInfoTable.h"
#include "OSY_CSVParseLibrary.h"
#include "OSY_HttpDownloader.h"
#include "OSY_HttpRequestActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "OSY_NiagaraSpawner.h"

void UOSY_PropWidget::NativeConstruct()
{
	btn_BoxSpawn->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnBox);
	btn_Save->OnClicked.AddDynamic(this, &UOSY_PropWidget::SaveJsonData);
	btn_Exit->OnClicked.AddDynamic(this, &UOSY_PropWidget::LevelTravel);
	btn_CSVSingle->OnClicked.AddDynamic(this, &UOSY_PropWidget::LoadJsonData);
	btn_CSVAll->OnClicked.AddDynamic(this, &UOSY_PropWidget::ReadCSVAll);

	btn_CSVFile->OnClicked.AddDynamic(this, &UOSY_PropWidget::ReadCSVFile);
	btn_SendCSV->OnClicked.AddDynamic(this, &UOSY_PropWidget::SendJSon);
	btn_PostCSV->OnClicked.AddDynamic(this, &UOSY_PropWidget::PostJSon);

	for (TActorIterator<AOSY_HttpRequestActor> it(GetWorld()); it; ++it)
	{
		HttpActor = *it;
	}

	factory = Cast<AOSY_NiagaraSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_NiagaraSpawner::StaticClass()));

}
#pragma region CSV
void UOSY_PropWidget::SpawnBox()
{
	FVector spawnLoc = FVector(200,0,0);
	FRotator spawnRot = FRotator(0,0,0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(proptest, spawnLoc, spawnRot);
		
		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale());
		}
	}
}

void UOSY_PropWidget::SaveJsonData()
{

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	// ������ �����͸� JSON ��ü�� �߰�

	// ������ �����͸� JSON �迭�� �߰�
	TArray<TSharedPtr<FJsonValue>> LocationsArray;
	TArray<TSharedPtr<FJsonValue>> RotationsArray;
	TArray<TSharedPtr<FJsonValue>> ScalesArray;

	for (const FVector& Location : SavedLocations)
	{
		TSharedPtr<FJsonObject> LocationObj = MakeShareable(new FJsonObject);
		LocationObj->SetNumberField(TEXT("X"), Location.X);
		LocationObj->SetNumberField(TEXT("Y"), Location.Y);
		LocationObj->SetNumberField(TEXT("Z"), Location.Z);
		LocationsArray.Add(MakeShareable(new FJsonValueObject(LocationObj)));
	}
	

// 	JsonObject->SetNumberField(TEXT("LocX"), SavedLocation.X);
// 	JsonObject->SetNumberField(TEXT("LocY"), SavedLocation.Y);
// 	JsonObject->SetNumberField(TEXT("LocZ"), SavedLocation.Z);
// 	JsonObject->SetNumberField(TEXT("ScaX"), SavedScale.X);
// 	JsonObject->SetNumberField(TEXT("ScaY"), SavedScale.Y);
// 	JsonObject->SetNumberField(TEXT("ScaZ"), SavedScale.Z);

	// JSON�� ���ڿ��� ��ȯ
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// JSON ���ڿ��� ���Ϸ� ����
	FString SavePath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");
	FFileHelper::SaveStringToFile(JsonString, *SavePath);
	UE_LOG(LogTemp, Warning, TEXT("path : %s"), *SavePath);


	UE_LOG(LogTemp, Warning, TEXT("Loc : X=%f, Y=%f, Z=%f"), SavedLocation.X, SavedLocation.Y, SavedLocation.Z);
	UE_LOG(LogTemp, Warning, TEXT("Rot : Pitch=%f, Yaw=%f, Roll=%f"), SavedRotation.Pitch, SavedRotation.Yaw, SavedRotation.Roll);
	UE_LOG(LogTemp, Warning, TEXT("Sca : X=%f, Y=%f, Z=%f"), SavedScale.X, SavedScale.Y, SavedScale.Z);

}

void UOSY_PropWidget::LoadJsonData()
{
	FString LoadPath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");

	// JSON ������ ���ڿ��� �о��
	FString JsonString;
	if (FFileHelper::LoadFileToString(JsonString, *LoadPath))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

		// JSON ���ڿ��� JSON ��ü�� �Ľ�
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// JSON ��ü���� �����͸� ����
			if (JsonObject->HasField(TEXT("LocX")) && JsonObject->HasField(TEXT("LocY")) && JsonObject->HasField(TEXT("LocZ")) && JsonObject->HasField(TEXT("ScaX")) && JsonObject->HasField(TEXT("ScaY")) && JsonObject->HasField(TEXT("ScaZ")))
			{
					float locX = JsonObject->GetNumberField(TEXT("LocX"));
					float locY = JsonObject->GetNumberField(TEXT("LocY"));
					float locZ = JsonObject->GetNumberField(TEXT("LocX"));
					float scaX = JsonObject->GetNumberField(TEXT("scaX"));
					float scaY = JsonObject->GetNumberField(TEXT("scaY"));
					float scaZ = JsonObject->GetNumberField(TEXT("scaX"));

					// ������ �����͸� ���
					FVector LoadedLocation(locX, locY, locZ);
					FVector LoadedScale(scaX, scaY, scaZ);

					UE_LOG(LogTemp, Warning, TEXT("sLoc : X=%f, Y=%f, Z=%f"), LoadedLocation.X, LoadedLocation.Y, LoadedLocation.Z);
					UE_LOG(LogTemp, Warning, TEXT("sSca : X=%f, Y=%f, Z=%f"), LoadedScale.X, LoadedScale.Y, LoadedScale.Z);
					// LoadedLocation�� ����ϰų� �ʿ��� ��� ó��
			}
		}
	}
}

void UOSY_PropWidget::LevelTravel()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(),LevelName,true);
}

// Ư�������� �����͸� �д� �Լ�
void UOSY_PropWidget::ReadCSVSingle()
{
	if (levelInfoTable != nullptr)
	{
		/*FLevelInfoTable* result = levelInfoTable->FindRow<FLevelInfoTable>("111111", "Level information");

		if (result != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Name : %s, Job : %s, HP : %d, MP:%d"),*result->name, *result->job,result->hp,result->mp);
		}
		*/
	}
}

void UOSY_PropWidget::ReadCSVAll()
{
	if (levelInfoTable != nullptr)
	{
		TArray<FLevelInfoTable*> levelInfoList;
		levelInfoTable->GetAllRows<FLevelInfoTable>("LevelDataList",levelInfoList);

		if (levelInfoList.Num() > 0)
		{
			FString resulText;
			for (FLevelInfoTable* levelInfo : levelInfoList)
			{

			}
		}
	}
}

void UOSY_PropWidget::ReadCSVFile()
{
	if (factory != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReadCSVFile Success"));
		factory->spawnStart();
	}
/*
	TArray<FLevelInfoTable> levelDataList;

	FString path="D:\\Unreal\\XR-Unreal\\Content\\CSVData\\levelInfo.csv";

	UOSY_CSVParseLibrary::ReadMyCSV(path, levelDataList);

	if (levelDataList.Num() > 0)
	{
		FString resultText;
		for (FLevelInfoTable levelInfo : levelDataList)
		{
			

			UE_LOG(LogTemp, Warning, TEXT("Name : %s, spawnTime : %f, dieTime : %f, locationX : %f,locationY : %f, locationZ : %f, scale : %f, texture : %d"), *levelInfo.name, levelInfo.spawnTime, levelInfo.dieTime, levelInfo.locationX, levelInfo.locationY, levelInfo.locationZ, levelInfo.scale,levelInfo.texture);
		}
	}
	*/
}

void UOSY_PropWidget::SendJSon()
{
	if (HttpActor != nullptr)
	{
		HttpActor->SendRequest(url);

	}
}

void UOSY_PropWidget::PostJSon()
{
	if (HttpActor != nullptr)
	{
		HttpActor->PostRequest(url);

	}
	
}
#pragma endregion






