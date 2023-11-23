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
#include "OSY_GameInstance.h"
#include "OSY_HttpRequestActor.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

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

    gi = Cast<UOSY_GameInstance>(GetGameInstance());
    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

    TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));

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

    Request();

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOSY_CreativeGameModeBase::SetMaxTimeFromSong, 2.0f, false);
}

void AOSY_CreativeGameModeBase::Tick(float DeltaTime)
{
    
}

void AOSY_CreativeGameModeBase::SetMaxTimeFromSong()
{
    // 선택한 노래의 이름을 가져옵니다.
    FString songName = PlaySong;

    // 노래의 경로를 생성합니다.
    FString songPath = FString::Printf(TEXT("/Game/DEV/Sounds/%s.%s"), *songName, *songName);
    ///Script/Engine.SoundWave'/Game/DEV/Sounds/Deep_Future_Garage.Deep_Future_Garage'

    // 노래를 로드합니다.
    Song = LoadObject<USoundBase>(nullptr, *songPath, nullptr, LOAD_None, nullptr);

    if (Song)
    {
        superShy=Song;
        SequnceUI->MaxTime = Song->Duration;
        int32 TotalSeconds = FMath::RoundToInt(Song->Duration);
        int32 Minutes = TotalSeconds / 60;
        int32 Seconds = TotalSeconds % 60;

        FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
        SequnceUI->tb_MaxTime->SetText(FText::FromString(TimeString));

        SequnceUI->tb_SongName->SetText(FText::FromString(songName));

    }

	
}

void AOSY_CreativeGameModeBase::Request()
{
    if (HttpActor != nullptr)
    {
        FString GiId=FString::FormatAsNumber(gi->PlayId);
        FString IdMapDetailInfo = gi->MapDetailInfo+"/"+GiId;
        HttpActor->SendRequest(IdMapDetailInfo);
    }
}


