// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_JsonParseLibrary.h"
#include "Json.h"
#include "Runtime/Json/Public/Serialization/JsonWriter.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"


FString UOSY_JsonParseLibrary::JsonParse(const FString& originData)
{

	FString parsedData;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	// ??????.
	if (FJsonSerializer::Deserialize(reader, result))
	{
		TArray<TSharedPtr<FJsonValue>> parsedDataArray = result->GetArrayField("");

		for (TSharedPtr<FJsonValue> pd : parsedDataArray)
		{
			int id = pd->AsObject()->GetIntegerField("id");
			int memberId = pd->AsObject()->GetIntegerField("memberId");
			FString title = pd->AsObject()->GetStringField("title");
			FString song = pd->AsObject()->GetStringField("song");
			FString data = pd->AsObject()->GetStringField("data");
			FString createdDate = pd->AsObject()->GetStringField("createdDate");
			UE_LOG(LogTemp, Warning, TEXT("% d :% d :% s :% s :% s :% s "), id, memberId, *title, *song, *data, *createdDate);

			parsedData.Append(FString::Printf(TEXT("% d :% d :% s :% s :% s :% s "), id, memberId, *title, *song, *data, *createdDate));
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
		// JSON ÆÄ½Ì ½ÇÆÐ
		UE_LOG(LogTemp, Error, TEXT("JSON ÆÄ½Ì ½ÇÆÐ: %s"), *Reader->GetErrorMessage());
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

