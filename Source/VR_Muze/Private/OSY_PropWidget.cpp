// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PropWidget.h"
#include "Components/Button.h"
#include "KJS_TestSpawnActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "LevelInfoTable.h"
#include "OSY_CSVParseLibrary.h"

void UOSY_PropWidget::NativeConstruct()
{
	btn_BoxSpawn->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnBox);
	btn_Save->OnClicked.AddDynamic(this, &UOSY_PropWidget::SaveData);
	btn_Exit->OnClicked.AddDynamic(this, &UOSY_PropWidget::LevelTravel);
	btn_CSVSingle->OnClicked.AddDynamic(this, &UOSY_PropWidget::ReadCSVSingle);
	btn_CSVAll->OnClicked.AddDynamic(this, &UOSY_PropWidget::ReadCSVAll);

	btn_CSVFile->OnClicked.AddDynamic(this, &UOSY_PropWidget::ReadCSVFile);

}

void UOSY_PropWidget::SpawnBox()
{
	FVector spawnLoc = FVector(0,0,0);
	FRotator spawnRot = FRotator(0,0,0);

	UWorld* World = GetWorld();
	if (World)
	{
		
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(proptest, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			// 스폰에 성공하면 추가적인 설정 및 로직을 구현할 수 있습니다.
			// 예를 들어, 프롭을 조작하거나 다른 작업을 수행할 수 있습니다.
		}
		
	}
}

void UOSY_PropWidget::SaveData()
{

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
		FLevelInfoTable* result = levelInfoTable->FindRow<FLevelInfoTable>("111111","Level information");

		if (result != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Name : %s, Job : %s, HP : %d, MP:%d"),*result->name, *result->job,result->hp,result->mp);
		}
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
				resulText.Append(FString::Printf(TEXT("Name : %s, Job : %s, HP : %d, MP:%d\n"), *levelInfo->name, *levelInfo->job, levelInfo->hp, levelInfo->mp));

				UE_LOG(LogTemp, Warning, TEXT("Name : %s, Job : %s, HP : %d, MP:%d\n"), *levelInfo->name, *levelInfo->job, levelInfo->hp, levelInfo->mp);

			}
		}
	}
}

void UOSY_PropWidget::ReadCSVFile()
{
	TArray<FLevelInfoTable*> levelDataList;

	FString path="D: / Unreal / XR - Unreal / Content / DEV / OOSY / CSVData / PlayerInfoTable.csv";

	UOSY_CSVParseLibrary::ReadMyCSV(path,levelDataList);

	UE_LOG(LogTemp,Warning,TEXT("Path : %s"),*path);
	UE_LOG(LogTemp,Warning,TEXT("LevelDataList : %d"),levelDataList.Num());


	if (levelDataList.Num() > 0)
	{
		FString resultText;
		for (FLevelInfoTable* levelInfo : levelDataList)
		{
			
			resultText.Append(FString::Printf(TEXT("Name: %s, Job: %s, HP: %d, MP: %d\r\n"), *levelInfo->name, *levelInfo->job, levelInfo->hp, levelInfo->mp));

		}
	}
}
