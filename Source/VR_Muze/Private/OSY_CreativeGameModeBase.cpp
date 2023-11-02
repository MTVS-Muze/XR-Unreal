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
    TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));

}

void AOSY_CreativeGameModeBase::BeginPlay()
{
    Super::BeginPlay();


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

    SetMaxTimeFromSong();

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

    SequnceUI->CurrentTime = TimeManager->CurrentTime;

    SequnceUI->UpdateProgressBar();
}

void AOSY_CreativeGameModeBase::SetMaxTimeFromSong()
{
    USoundWave* Song = LoadObject<USoundWave>(nullptr, TEXT("/Game/DEV/Sounds/SuperShy.SuperShy"), nullptr, LOAD_None, nullptr);

    if (Song)
    {
        SequnceUI->MaxTime = Song->Duration;
    }
}

