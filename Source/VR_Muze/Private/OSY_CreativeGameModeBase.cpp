// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CreativeGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "LevelInfoTable.h"
#include "OSY_PropWidget.h"
#include "OSY_SequenceWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_TImeActor.h"

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

    //TimeActorIns = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass())) ;
    

    

    httpUI = CreateWidget<UOSY_PropWidget>(GetWorld(), httpWidget);
    if (httpUI != nullptr)
    {
        httpUI->AddToViewport();
    }

    SequnceUI = CreateWidget<UOSY_SequenceWidget>(GetWorld(),SequenceWidget);
    if (SequnceUI != nullptr)
    {
        SequnceUI->AddToViewport();
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

    // MaxTime에 120초를 할당
    SequnceUI->MaxTime = 10.0f;

    // CurrentTime을 업데이트 (예: 60초)
    SequnceUI->CurrentTime = httpUI->CurrentTime;

    // 시간 업데이트
    SequnceUI->UpdateProgressBar();
}

