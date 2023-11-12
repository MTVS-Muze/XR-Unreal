// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CreativeGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "LevelInfoTable.h"
#include "OSY_PropWidget.h"
#include "OSY_SequenceWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_TImeActor.h"
#include "OSY_LoginWidget.h"
#include "OSY_OutLinerWidget.h"

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

    SequnceUI = CreateWidget<UOSY_SequenceWidget>(GetWorld(), SequenceWidget);
    if (SequnceUI != nullptr)
    {
        SequnceUI->AddToViewport();
    }

    OutLinerUI = CreateWidget<UOSY_OutLinerWidget>(GetWorld(), OutLinerWidget);
    if (OutLinerUI != nullptr)
    {
        OutLinerUI->AddToViewport();
    }

    SetMaxTimeFromSong();

    if (LevelInfoTable != nullptr)
    {
        for (int32 i = 1; i <= LevelInfoTable->GetRowNames().Num(); i++)
        {
            FLevelInfoTable* LevelInfo = LevelInfoTable->FindRow<FLevelInfoTable>(FName(*(FString::FormatAsNumber(i))), FString(""));

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

    if (SequnceUI != nullptr && TimeManager != nullptr)
    {
        SequnceUI->CurrentTime = TimeManager->CurrentTime;
        SequnceUI->UpdateProgressBar();
    }
    else
    {
        if (SequnceUI == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("SequnceUI is null."));
        }
        if (TimeManager == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("TimeManager is null."));
        }
    }
}

void AOSY_CreativeGameModeBase::Tick(float DeltaTime)
{
    
}

void AOSY_CreativeGameModeBase::SetMaxTimeFromSong()
{
    USoundWave* Song = LoadObject<USoundWave>(nullptr, TEXT("/Game/DEV/Sounds/SuperShy.SuperShy"), nullptr, LOAD_None, nullptr);

    if (Song)
    {
        SequnceUI->MaxTime = Song->Duration;
    }
}



