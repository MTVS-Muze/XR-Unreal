// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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

	static FString LevelJsonParse(const FString& originData);

	TSharedPtr<FJsonObject> ParseJSON(const FString& JSONString);
	
	static FString MakeJson(TMap<FString, FString> source);

	
	
};
