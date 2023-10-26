// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CreativeGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "LevelInfoTable.h"
#include "OSY_PropWidget.h"

AOSY_CreativeGameModeBase::AOSY_CreativeGameModeBase()
{
    ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/CSVData/levelInfo.levelInfo"));
    if (DataTable.Succeeded())
    {
        LevelInfoTable = DataTable.Object;
    }

   

}

void AOSY_CreativeGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    httpUI = CreateWidget<UOSY_PropWidget>(GetWorld(), httpWidget);
    if (httpUI != nullptr)
    {
        httpUI->AddToViewport();
    }

    if (LevelInfoTable != nullptr)
    {
        for (int32 i = 1; i <= LevelInfoTable->GetRowNames().Num(); i++)
        {
            FLevelInfoTable* LevelInfo = LevelInfoTable->FindRow<FLevelInfoTable>(FName(*(FString::FormatAsNumber(i))),FString(""));
        

            UE_LOG(LogTemp, Warning, TEXT("name : %s"), *LevelInfo->name);
            UE_LOG(LogTemp, Warning, TEXT("spawnTime : %f"), LevelInfo->spawnTime);
            UE_LOG(LogTemp, Warning, TEXT("dieTime : %f"), LevelInfo->dieTime);
            UE_LOG(LogTemp, Warning, TEXT("locationX : %f"), LevelInfo->locationX);
            UE_LOG(LogTemp, Warning, TEXT("locationY : %f"), LevelInfo->locationY);
            UE_LOG(LogTemp, Warning, TEXT("locationZ : %f"), LevelInfo->locationZ);
            UE_LOG(LogTemp, Warning, TEXT("scale : %f"), LevelInfo->scale);
            UE_LOG(LogTemp, Warning, TEXT("texture : %d"), LevelInfo->texture);

           
        }
    }
}

