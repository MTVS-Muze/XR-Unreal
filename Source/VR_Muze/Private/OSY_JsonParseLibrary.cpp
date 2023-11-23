// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_JsonParseLibrary.h"
#include "Json.h"
#include "Runtime/Json/Public/Serialization/JsonWriter.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "KJS_GameModeBase.h"
#include "Dom/JsonObject.h"


FString UOSY_JsonParseLibrary::PlayerInfoJsonParse(const FString& originData)
{
	FString parsedData;

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	// JSON �����͸� �Ľ�
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

	// JSON �����͸� �Ľ�
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
		// �� ��ü�� ����
		for (auto& Item : items)
		{
			TSharedPtr<FJsonObject> DataObject = Item->AsObject();

			// �ʵ� �б�
			FAllLevelData Data;
			Data.Id = DataObject->GetIntegerField("id");
			Data.MemberName = DataObject->GetStringField("memberName");
			Data.Title = DataObject->GetStringField("title");
			Data.Song = DataObject->GetStringField("song");
			Data.Singer = DataObject->GetStringField("singer");
			Data.Info = DataObject->GetStringField("info");
			Data.Data = DataObject->GetStringField("data");
			Data.CreatedDate = DataObject->GetStringField("createdDate");

			// �迭�� �߰�
			AllLevelArray.Add(Data);
		}
	}

	return AllLevelArray;

}


void UOSY_JsonParseLibrary::LevelJsonParse(const FString& OriginData, AOSY_CreativeGameModeBase* GameMode)
{

	UE_LOG(LogTemp, Warning, TEXT("originData:%s"), *OriginData);

	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(OriginData);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		FString Data = JsonObject->GetStringField("data");
		FString Song = JsonObject->GetStringField("song");
		GameMode->PlaySong = Song;
		//UE_LOG(LogTemp,Warning,TEXT("Song :%s"),*Song);

		TSharedRef<TJsonReader<TCHAR>> DataReader = TJsonReaderFactory<TCHAR>::Create(Data);
		TSharedPtr<FJsonObject> DataJsonObject = MakeShareable(new FJsonObject);

		if (FJsonSerializer::Deserialize(DataReader, DataJsonObject) && DataJsonObject.IsValid())
		{
			TArray<TSharedPtr<FJsonValue>> Locations = DataJsonObject->GetArrayField(TEXT("Locations"));
			TArray<TSharedPtr<FJsonValue>> Rotations = DataJsonObject->GetArrayField(TEXT("Rotations"));
			TArray<TSharedPtr<FJsonValue>> Scales = DataJsonObject->GetArrayField(TEXT("Scales"));
			TArray<TSharedPtr<FJsonValue>> ActorClasses = DataJsonObject->GetArrayField(TEXT("ActorClasses"));
			TArray<TSharedPtr<FJsonValue>> SpawnTime = DataJsonObject->GetArrayField(TEXT("SpawnTime"));
			TArray<TSharedPtr<FJsonValue>> LifeSpan = DataJsonObject->GetArrayField(TEXT("LifeSpan"));

			for (int32 i = 0; i < Locations.Num(); i++)
			{
				TSharedPtr<FJsonObject> Location = Locations[i]->AsObject();
				TSharedPtr<FJsonObject> Rotation = Rotations[i]->AsObject();
				TSharedPtr<FJsonObject> Scale = Scales[i]->AsObject();

				FVector LocationVector(Location->GetNumberField("X"), Location->GetNumberField("Y"), Location->GetNumberField("Z"));
				FRotator RotationVector(Rotation->GetNumberField("Pitch"), Rotation->GetNumberField("Yaw"), Rotation->GetNumberField("Roll"));
				FVector ScaleVector(Scale->GetNumberField("X"), Scale->GetNumberField("Y"), Scale->GetNumberField("Z"));

				FString ActorClass = ActorClasses[i]->AsString();
				float SpawnTimeValue = SpawnTime[i]->AsNumber();
				float LifeSpanValue = LifeSpan[i]->AsNumber();

				// �� �������� GameMode�� �����鿡 �����մϴ�.
				GameMode->Locations.Add(LocationVector);
				GameMode->Rotations.Add(RotationVector);
				GameMode->Scales.Add(ScaleVector);
				GameMode->ActorClasses.Add(ActorClass);
				GameMode->SpawnTimes.Add(SpawnTimeValue);
				GameMode->LifeSpans.Add(LifeSpanValue);
			}
		}
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
		// JSON �Ľ� ����
		UE_LOG(LogTemp, Error, TEXT("JSON �Ľ� ����: %s"), *Reader->GetErrorMessage());
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

FVector UOSY_JsonParseLibrary::ParseFVector(const FString& Str)
{
	FVector Result;

	// ���ڿ��� ','�� �и�
	TArray<FString> Tokens;
	Str.ParseIntoArray(Tokens, TEXT(","), true);

	// �� ��ū�� float���� ��ȯ
	if (Tokens.Num() == 3)
	{
		Result.X = FCString::Atof(*Tokens[0]);
		Result.Y = FCString::Atof(*Tokens[1]);
		Result.Z = FCString::Atof(*Tokens[2]);
	}

	return Result;
}

FRotator UOSY_JsonParseLibrary::ParseFRotator(const FString& Str)
{
	FRotator Result;

	// ���ڿ��� ','�� �и�
	TArray<FString> Tokens;
	Str.ParseIntoArray(Tokens, TEXT(","), true);

	// �� ��ū�� float���� ��ȯ
	if (Tokens.Num() == 3)
	{
		Result.Pitch = FCString::Atof(*Tokens[0]);
		Result.Yaw = FCString::Atof(*Tokens[1]);
		Result.Roll = FCString::Atof(*Tokens[2]);
	}

	return Result;
}

