// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_JsonParseLibrary.h"
#include "Json.h"
#include "Runtime/Json/Public/Serialization/JsonWriter.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"


FString UOSY_JsonParseLibrary::PlayerJsonParse(const FString& originData)
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

FString UOSY_JsonParseLibrary::LevelJsonParse(const FString& originData)
{
	FString parsedData;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	// JSON 데이터를 파싱
	if (FJsonSerializer::Deserialize(reader, result) && result.IsValid())
	{
		int id = result->GetIntegerField("id");
		FString memberId = result->GetStringField("memberId");
		FString title = result->GetStringField("title");
		FString song = result->GetStringField("song");
		FString singer = result->GetStringField("singer");
		FString info = result->GetStringField("info");
		FString data = result->GetStringField("data");
		FString createdDate = result->GetStringField("createdDate");

		TSharedRef<TJsonReader<TCHAR>> dataReader = TJsonReaderFactory<TCHAR>::Create(data);
		TSharedPtr<FJsonObject> dataResult = MakeShareable(new FJsonObject());
		/**/
		if (FJsonSerializer::Deserialize(dataReader, dataResult) && dataResult.IsValid())
		{
			TArray<TSharedPtr<FJsonValue>> locations = dataResult->GetArrayField("Locations");
			TArray<TSharedPtr<FJsonValue>> rotations = dataResult->GetArrayField("Rotations");
			TArray<TSharedPtr<FJsonValue>> scales = dataResult->GetArrayField("Scales");
			TArray<TSharedPtr<FJsonValue>> actorClasses = dataResult->GetArrayField("ActorClasses");
			//TArray<double> spawnTime = dataResult->GetArrayField("SpawnTime");
			//TArray<int32> lifeSpan = dataResult->GetArrayField("LifeSpan");

			// 각 배열을 순회하며 필요한 정보를 추출
			for (auto& location : locations)
			{
				TSharedPtr<FJsonObject> locationObj = location->AsObject();
				float x = locationObj->GetNumberField("X");
				float y = locationObj->GetNumberField("Y");
				float z = locationObj->GetNumberField("Z");

				// ...
			}

			// rotations, scales 등에 대해서도 비슷하게 처리
			// ...

			for (auto& actorClass : actorClasses)
			{
				FString actorClassName = actorClass->AsString();

				// ...
			}

			//for (double time : spawnTime)
			{
				// ...
			}

			//for (int32 span : lifeSpan)
			{
				// ...
			}
		}
	}

	return parsedData;
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

