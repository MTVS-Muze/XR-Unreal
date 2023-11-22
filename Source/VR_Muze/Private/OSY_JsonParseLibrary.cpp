// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_JsonParseLibrary.h"
#include "Json.h"
#include "Runtime/Json/Public/Serialization/JsonWriter.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "KJS_GameModeBase.h"


FString UOSY_JsonParseLibrary::PlayerInfoJsonParse(const FString& originData)
{
	FString parsedData;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	// JSON 데이터를 파싱
	if (FJsonSerializer::Deserialize(reader, result) && result.IsValid())
	{
		int id = result->GetIntegerField("id");
		FString name = result->GetStringField("name");
		FString sub = result->GetStringField("sub");
		FString profileImage = result->GetStringField("profileImage");
		FString platform = result->GetStringField("platform");
		FString role = result->GetStringField("role");
		FString email = result->GetStringField("email");


		UE_LOG(LogTemp, Warning, TEXT("%d:%s:%s:%s:%s:%s:%s"), id, *name, *sub, *profileImage, *platform, *role, *email);

		parsedData = FString::Printf(TEXT("%d:%s:%s:%s:%s:%s:%s"), id, *name, *sub, *profileImage, *platform, *role, *email);
	}

	return parsedData;
}

FString UOSY_JsonParseLibrary::PlayerCustomJsonParse(const FString& originData)
{

	FString parsedData;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	// JSON 데이터를 파싱
	if (FJsonSerializer::Deserialize(reader, result) && result.IsValid())
	{
		int color = result->GetIntegerField("color");
		int hat = result->GetIntegerField("hat");
		int glass = result->GetIntegerField("glass");
		int tie = result->GetIntegerField("tie");
		
		parsedData = FString::Printf(TEXT("%d:%d:%d"), color,hat, glass, tie);
	}

	return parsedData;
}

TArray<FAllLevelData>  UOSY_JsonParseLibrary::AllLevelJsonParse(const FString& originData)
{
	TArray<FAllLevelData> AllLevelArray;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	TArray<TSharedPtr<FJsonValue>> items;

	if (FJsonSerializer::Deserialize(reader, items))
	{
		// 각 객체에 대해
		for (auto& Item : items)
		{
			TSharedPtr<FJsonObject> DataObject = Item->AsObject();

			// 필드 읽기
			FAllLevelData Data;
			Data.Id = DataObject->GetIntegerField("id");
			Data.MemberName = DataObject->GetStringField("memberName");
			Data.Title = DataObject->GetStringField("title");
			Data.Song = DataObject->GetStringField("song");
			Data.Singer = DataObject->GetStringField("singer");
			Data.Info = DataObject->GetStringField("info");
			Data.Data = DataObject->GetStringField("data");
			Data.CreatedDate = DataObject->GetStringField("createdDate");

			// 배열에 추가
			AllLevelArray.Add(Data);
		}
	}

	return AllLevelArray;

}


void UOSY_JsonParseLibrary::LevelJsonParse(const FString& OriginData, AOSY_CreativeGameModeBase* GameMode)
{

	UE_LOG(LogTemp,Warning,TEXT("originData:%s"),*OriginData);
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(OriginData);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		FString Data = JsonObject->GetStringField("data");

		TSharedRef<TJsonReader<TCHAR>> DataReader = TJsonReaderFactory<TCHAR>::Create(Data);
		TSharedPtr<FJsonObject> DataJsonObject = MakeShareable(new FJsonObject);

		if (FJsonSerializer::Deserialize(DataReader, DataJsonObject) && DataJsonObject.IsValid())
		{
			// 각 배열을 순회하며 필요한 정보를 추출
			for (auto& Location : DataJsonObject->GetArrayField("Locations"))
			{
				TSharedPtr<FJsonObject> LocationObj = Location->AsObject();
				GameMode->Locations.Add(FVector(LocationObj->GetNumberField("X"), LocationObj->GetNumberField("Y"), LocationObj->GetNumberField("Z")));
			}

			for (auto& Rotation : DataJsonObject->GetArrayField("Rotations"))
			{
				TSharedPtr<FJsonObject> RotationObj = Rotation->AsObject();
				GameMode->Rotations.Add(FRotator(RotationObj->GetNumberField("X"), RotationObj->GetNumberField("Y"), RotationObj->GetNumberField("Z")));
			}

			for (auto& Scale : DataJsonObject->GetArrayField("Scales"))
			{
				TSharedPtr<FJsonObject> ScaleObj = Scale->AsObject();
				GameMode->Scales.Add(FVector(ScaleObj->GetNumberField("X"), ScaleObj->GetNumberField("Y"), ScaleObj->GetNumberField("Z")));
			}

			for (auto& ActorClass : DataJsonObject->GetArrayField("ActorClasses"))
			{
				GameMode->ActorClasses.Add(ActorClass->AsString());
			}

			for (auto& SpawnTime : DataJsonObject->GetArrayField("SpawnTime"))
			{
				GameMode->SpawnTimes.Add(SpawnTime->AsNumber());
			}

			for (auto& LifeSpan : DataJsonObject->GetArrayField("LifeSpan"))
			{
				GameMode->LifeSpans.Add(LifeSpan->AsNumber());
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Locations:"));
	for (const FVector& Location : GameMode->Locations)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Location.ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("Rotations:"));
	for (const FRotator& Rotation : GameMode->Rotations)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Rotation.ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("Scales:"));
	for (const FVector& Scale : GameMode->Scales)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Scale.ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("ActorClasses:"));
	for (const FString& ActorClass : GameMode->ActorClasses)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorClass);
	}

	UE_LOG(LogTemp, Warning, TEXT("SpawnTimes:"));
	for (double SpawnTime : GameMode->SpawnTimes)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), SpawnTime);
	}

	UE_LOG(LogTemp, Warning, TEXT("LifeSpans:"));
	for (int32 LifeSpan : GameMode->LifeSpans)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), LifeSpan);
	}
}

TSharedPtr<FJsonObject> UOSY_JsonParseLibrary::ParseJSON(const FString& JSONString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JSONString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		return JsonObject;
	}

	else
	{
		// JSON 파싱 실패
		UE_LOG(LogTemp, Error, TEXT("JSON 파싱 실패: %s"), *Reader->GetErrorMessage());
		return nullptr;
	}
}

FString UOSY_JsonParseLibrary::MakeJson(TMap<FString, FString> source)
{
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> Keyvalue : source)
	{
		jsonObj->SetStringField(Keyvalue.Key, Keyvalue.Value);
	}

	FString jsonData;

	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);
	FJsonSerializer::Serialize(jsonObj.ToSharedRef(), writer);

	return jsonData;
}

