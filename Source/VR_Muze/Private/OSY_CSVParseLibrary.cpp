// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CSVParseLibrary.h"
#include "LevelInfoTable.h"

void UOSY_CSVParseLibrary::ReadMyCSV(FString filePath, TArray< FLevelInfoTable*>& levelInfoList)
{
	FString rawCSV;
	FFileHelper::LoadFileToString(rawCSV,nullptr, *filePath);

	
	const TCHAR* delimeter1[] = { TEXT("\r"),TEXT("\n") };
	TArray<FString> lineData;
	rawCSV.ParseIntoArray(lineData, delimeter1, false);
	//levelInfoList.SetNum(lineData.Num()-1);



	//UE_LOG(LogTemp, Warning, TEXT("Line :%s"), lineData.Num());
	
	for (int32 i = 1; i < lineData.Num(); i++)
	{
		TArray<FString> columnData;
		const TCHAR* delimeter2 = TEXT(",");
		lineData[i].ParseIntoArray(columnData, delimeter2, false);


		UE_LOG(LogTemp, Warning, TEXT("Colum :%s"), columnData.Num());

		levelInfoList[i-1]->Set(columnData[1],columnData[2],FCString::Atoi(*columnData[3]), FCString::Atoi(*columnData[4]));
	}
	
}


