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

	// 저장할 데이터를 JSON 객체에 추가
	TArray<TSharedPtr<FJsonValue>> LocationsArray;
	TArray<TSharedPtr<FJsonValue>> RotationsArray;
	TArray<TSharedPtr<FJsonValue>> ScalesArray;

	for (int i = 0; i < SavedLocations.Num(); i++) {
		TSharedPtr<FJsonObject> LocationObj = MakeShareable(new FJsonObject);
		LocationObj->SetNumberField(TEXT("X"), SavedLocations[i].X);
		LocationObj->SetNumberField(TEXT("Y"), SavedLocations[i].Y);
		LocationObj->SetNumberField(TEXT("Z"), SavedLocations[i].Z);
		LocationsArray.Add(MakeShareable(new FJsonValueObject(LocationObj)));

		TSharedPtr<FJsonObject> RotationObj = MakeShareable(new FJsonObject);
		RotationObj->SetNumberField(TEXT("Pitch"), SavedRotations[i].Pitch);
		RotationObj->SetNumberField(TEXT("Yaw"), SavedRotations[i].Yaw);
		RotationObj->SetNumberField(TEXT("Roll"), SavedRotations[i].Roll);
		RotationsArray.Add(MakeShareable(new FJsonValueObject(RotationObj)));

		TSharedPtr<FJsonObject> ScaleObj = MakeShareable(new FJsonObject);
		ScaleObj->SetNumberField(TEXT("X"), SavedScales[i].X);
		ScaleObj->SetNumberField(TEXT("Y"), SavedScales[i].Y);
		ScaleObj->SetNumberField(TEXT("Z"), SavedScales[i].Z);
		ScalesArray.Add(MakeShareable(new FJsonValueObject(ScaleObj)));
	}

	JsonObject->SetArrayField(TEXT("Locations"), LocationsArray);
	JsonObject->SetArrayField(TEXT("Rotations"), RotationsArray);
	JsonObject->SetArrayField(TEXT("Scales"), ScalesArray);

	// JSON을 문자열로 변환
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	// JSON 문자열을 파일로 저장
	FString SavePath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");
	FFileHelper::SaveStringToFile(JsonString, *SavePath);
	UE_LOG(LogTemp, Warning, TEXT("path : %s"), *SavePath);

}

void UOSY_PropWidget::LoadJsonData()
{
	FString LoadPath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");

	// JSON 파일을 문자열로 읽어옴
	FString JsonString;
	if (FFileHelper::LoadFileToString(JsonString, *LoadPath))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

		// JSON 문자열을 JSON 객체로 파싱
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// JSON 객체에서 데이터를 추출
			if (JsonObject->HasField(TEXT("Locations")) && JsonObject->HasField(TEXT("Rotations")) && JsonObject->HasField(TEXT("Scales")))
			{
				TArray<TSharedPtr<FJsonValue>> LocationsArray = JsonObject->GetArrayField(TEXT("Locations"));
				TArray<TSharedPtr<FJsonValue>> RotationsArray = JsonObject->GetArrayField(TEXT("Rotations"));
				TArray<TSharedPtr<FJsonValue>> ScalesArray = JsonObject->GetArrayField(TEXT("Scales"));

				UWorld* World = GetWorld();
				if (World)
				{
					for (int i = 0; i < LocationsArray.Num(); i++)
					{
						TSharedPtr<FJsonObject> LocationObj = LocationsArray[i]->AsObject();
						TSharedPtr<FJsonObject> RotationObj = RotationsArray[i]->AsObject();
						TSharedPtr<FJsonObject> ScaleObj = ScalesArray[i]->AsObject();

						FVector LoadedLocation(LocationObj->GetNumberField(TEXT("X")), LocationObj->GetNumberField(TEXT("Y")), LocationObj->GetNumberField(TEXT("Z")));
						FRotator LoadedRotation(RotationObj->GetNumberField(TEXT("Pitch")), RotationObj->GetNumberField(TEXT("Yaw")), RotationObj->GetNumberField(TEXT("Roll")));
						FVector LoadedScale(ScaleObj->GetNumberField(TEXT("X")), ScaleObj->GetNumberField(TEXT("Y")), ScaleObj->GetNumberField(TEXT("Z")));

						UE_LOG(LogTemp, Warning, TEXT("sLoc : X=%f, Y=%f, Z=%f"), LoadedLocation.X, LoadedLocation.Y, LoadedLocation.Z);
						UE_LOG(LogTemp, Warning, TEXT("sRot : Pitch=%f, Yaw=%f, Roll=%f"), LoadedRotation.Pitch, LoadedRotation.Yaw, LoadedRotation.Roll);
						UE_LOG(LogTemp, Warning, TEXT("sSca : X=%f, Y=%f, Z=%f"), LoadedScale.X, LoadedScale.Y, LoadedScale.Z);

						// 액터를 스폰
						FActorSpawnParameters Params;
						Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						AActor* SpawnedActor = World->SpawnActor<AActor>(proptest, LoadedLocation, LoadedRotation, Params);
						if (SpawnedActor)
						{
							SpawnedActor->SetActorScale3D(LoadedScale);
						}
					}
				}
			}
		}
	}
}

void UOSY_PropWidget::LevelTravel()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(),LevelName,true);
}

// 특정라인의 데이터를 읽는 함수
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






