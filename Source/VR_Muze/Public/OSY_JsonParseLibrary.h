// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KJS_GameModeBase.h"
#include "OSY_CreativeGameModeBase.h"
#include "OSY_JsonParseLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_JsonParseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString PlayerInfoJsonParse(const FString& originData);
	
	static FString PlayerCustomJsonParse(const FString& originData);

	static TArray<FAllLevelData> AllLevelJsonParse(const FString& originData);

	static void LevelJsonParse(const FString& OriginData, AOSY_CreativeGameModeBase* GameMode);
	

	TSharedPtr<FJsonObject> ParseJSON(const FString& JSONString);
	
	static FString MakeJson(TMap<FString, FString> source);

	static FVector ParseFVector(const FString& Str);

	static FRotator ParseFRotator(const FString& Str);

	
};
