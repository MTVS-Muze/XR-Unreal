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
	Super::NativeConstruct();

	btn_BoxSpawn->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnBox);
	btn_SphereSpawn->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnSphere);
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


void UOSY_PropWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bShouldTick)
	{

	CurrentTime+=InDeltaTime;
	}

	UE_LOG(LogTemp,Warning,TEXT("%f"),CurrentTime)

	for (int32 i = PendingSpawns.Num() - 1; i >= 0; --i)
	{
		const FActorSpawnInfo& SpawnInfo = PendingSpawns[i];
		if (CurrentTime >= SpawnInfo.SpawnTime)
		{
			// 액터를 생성합니다.
			UWorld* World = GetWorld();
			if (World && SpawnInfo.ActorClass)
			{
				FActorSpawnParameters Params;
				Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AActor* SpawnedActor = World->SpawnActor<AActor>(SpawnInfo.ActorClass, SpawnInfo.Location, SpawnInfo.Rotation, Params);
				if (SpawnedActor)
				{
					SpawnedActor->SetActorScale3D(SpawnInfo.Scale);
					SpawnedActor->SetActorHiddenInGame(false);
				}
			}

			// 생성한 액터의 정보는 리스트에서 제거합니다.
			PendingSpawns.RemoveAt(i);
		}
	}
}

#pragma region CSV
void UOSY_PropWidget::SpawnBox()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

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
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(proptest);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SpawnSphere()
{
	FVector spawnLoc = FVector(200, -200, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), HttpActor->currenTime);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Sphereproptest, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Sphereproptest);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SaveJsonData()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> LocationsArray;
	TArray<TSharedPtr<FJsonValue>> RotationsArray;
	TArray<TSharedPtr<FJsonValue>> ScalesArray;
	TArray<TSharedPtr<FJsonValue>> ActorClassesArray;
	TArray<TSharedPtr<FJsonValue>> SpawnTimeArray;

	for (int i = 0; i < SavedLocations.Num(); i++)
	{
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

		ActorClassesArray.Add(MakeShareable(new FJsonValueString(SavedActorClasses[i]->GetName())));
		SpawnTimeArray.Add(MakeShareable(new FJsonValueNumber(SavedSpawnTimes[i])));

	}

	JsonObject->SetArrayField(TEXT("Locations"), LocationsArray);
	JsonObject->SetArrayField(TEXT("Rotations"), RotationsArray);
	JsonObject->SetArrayField(TEXT("Scales"), ScalesArray);
	JsonObject->SetArrayField(TEXT("ActorClasses"), ActorClassesArray);
	JsonObject->SetArrayField(TEXT("SpawnTime"), SpawnTimeArray);

	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	FString SavePath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");
	FFileHelper::SaveStringToFile(JsonString, *SavePath);
}

void UOSY_PropWidget::LoadJsonData()
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
					UClass* ActorClass = FindObject<UClass>(ANY_PACKAGE, *ActorClassName);

					float SavedTime = SpawnTimeArray[i]->AsNumber();

					// 액터 생성 정보를 구조체에 저장하고, 이를 리스트에 추가합니다.
					FActorSpawnInfo SpawnInfo;
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
	bShouldTick = true;
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






