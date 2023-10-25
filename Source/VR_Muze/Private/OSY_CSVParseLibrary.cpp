// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CSVParseLibrary.h"
#include "LevelInfoTable.h"

void UOSY_CSVParseLibrary::ReadMyCSV(FString filePath, TArray< FLevelInfoTable>& levelInfoList)
{
	FString rawCSV;
	FFileHelper::LoadFileToString(rawCSV, *filePath);

	
	const TCHAR* delimeter1[] = { TEXT("\r"),TEXT("\n") };
	TArray<FString> lineData;
	rawCSV.ParseIntoArray(lineData, delimeter1, 2, true);

	for (int32 i = 1; i < lineData.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *lineData[i]);
		TArray<FString> columnData;
		const TCHAR* delimeter2 = TEXT(",");
		lineData[i].ParseIntoArray(columnData, delimeter2, false);


		UE_LOG(LogTemp, Warning, TEXT("Colum :%d"), columnData.Num());

		if (columnData.Num() >= 8) {
			FLevelInfoTable NewLevelInfo;
			NewLevelInfo.Set(columnData[0], FCString::Atof(*columnData[1]), FCString::Atof(*columnData[2]), FCString::Atof(*columnData[3]), FCString::Atof(*columnData[4]), FCString::Atof(*columnData[5]), FCString::Atof(*columnData[6]), FCString::Atoi(*columnData[7]));
			levelInfoList.Add(NewLevelInfo);
		}

	}
	
}

TArray<FString> UOSY_CSVParseLibrary::ParseCSVFile(const FString& CSVData)
{
	TArray<FString> ParsedData;

	// CSV 데이터를 파싱합니다.
	TArray<FString> CSVLines;
	CSVData.ParseIntoArray(CSVLines, TEXT("\n"), false);

	// 각 줄을 반복하여 데이터를 파싱합니다.
	for (const FString& Line : CSVLines)
	{
		// 쉼표(,)로 구분된 데이터를 파싱합니다.
		TArray<FString> CSVFields;
		Line.ParseIntoArray(CSVFields, TEXT(","), false);

		// CSV 데이터를 ParsedData 배열에 추가합니다.
		for (const FString& Data : CSVFields)
		{
			ParsedData.Add(Data);
		}
	}

	return ParsedData;
}

FString UOSY_CSVParseLibrary::MakeCSV(TArray<TMap<FString, FString>> data)
{
	FString csvData;

	for (const TMap<FString, FString>& rowData : data)
	{
		for (auto It = rowData.CreateConstIterator(); It; ++It)
		{
			csvData += It.Key();
			csvData += TEXT(",");
			csvData += It.Value();
			csvData += TEXT(",");
		}
		// 각 행의 마지막 쉼표 제거
		csvData.RemoveAt(csvData.Len() - 1, 1);
		csvData += TEXT("\n");
	}

	return csvData;
	
}

