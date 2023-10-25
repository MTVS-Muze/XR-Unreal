// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "OSY_CSVParseLibrary.generated.h"




UCLASS()
class VR_MUZE_API UOSY_CSVParseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static void ReadMyCSV(FString filePath, TArray<struct FLevelInfoTable>& levelInfoList);

	static TArray<FString> ParseCSVFile(const FString& CSVData);

	static FString MakeCSV(TArray<TMap<FString, FString>> data);
	
};
