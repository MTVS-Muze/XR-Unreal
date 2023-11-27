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

void AOSY_CreativeGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    FTimerHandle TimerHandle;

    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOSY_CreativeGameModeBase::Request, 0.5f, false);


    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOSY_CreativeGameModeBase::LoadJsonData, 2.0f, false); 


    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOSY_CreativeGameModeBase::Play, 5.0f, false);
}

AOSY_CreativeGameModeBase::AOSY_CreativeGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AOSY_CreativeGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    gi = Cast<UOSY_GameInstance>(GetGameInstance());
  

    TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));

    FString MapName = GetWorld()->GetMapName();
    MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

    if (MapName.Contains("Ocean"))

    {
       
        
        Request();
    }
    else
    {
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


    Request();
}

void AOSY_CreativeGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);




    CurrentTime = TimeManager->CurrentTime;

 }

void AOSY_CreativeGameModeBase::SetMaxTimeFromSong()
{
    // 선택한 노래의 이름을 가져옵니다.
    FString songName = gi->song;

    // 노래의 경로를 생성합니다.
    FString songPath = FString::Printf(TEXT("/Game/DEV/Sounds/%s.%s"), *songName, *songName);
    ///Script/Engine.SoundWave'/Game/DEV/Sounds/Deep_Future_Garage.Deep_Future_Garage'

    // 노래를 로드합니다.
    Song = LoadObject<USoundBase>(nullptr, *songPath, nullptr, LOAD_None, nullptr);

    if (Song)
    {
        SequnceUI->MaxTime = Song->Duration;
        superShy=Song;
        int32 TotalSeconds = FMath::RoundToInt(Song->Duration);
        int32 Minutes = TotalSeconds / 60;
        int32 Seconds = TotalSeconds % 60;

        FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
        SequnceUI->tb_Maxtime->SetText(FText::FromString(TimeString));
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

void AOSY_CreativeGameModeBase::LoadJsonData()
{

    // gm에 있는 데이터를 PendingSpawns에 추가한다.
    UE_LOG(LogTemp, Warning, TEXT("PendingSpawns size: %d"), PendingSpawns.Num());

    for (int i = 0; i < Locations.Num(); i++)
    {
        FLevelInfo2 pendingSpawn;
        pendingSpawn.Location = Locations[i];
        pendingSpawn.Rotation = Rotations[i];
        pendingSpawn.Scale = Scales[i];


        FString BlueprintName = ActorClasses[i];
        BlueprintName = BlueprintName.Replace(TEXT("_C"), TEXT(""));
        FString BlueprintHame = ActorClasses[i];
        FString BlueprintPath = FString::Printf(TEXT("/Game/DEV/OOSY/Blueprints/BP_Niagara/%s.%s"), *BlueprintName, *BlueprintHame);


        UClass* ActorClass = LoadObject<UClass>(nullptr, *BlueprintPath);
        pendingSpawn.ActorClass = ActorClass;

        pendingSpawn.SpawnTime = SpawnTimes[i];
        pendingSpawn.LifeSpan = LifeSpans[i];

        PendingSpawns.Add(pendingSpawn);


    }

    TimeManager->bShouldTick = true;
}

void AOSY_CreativeGameModeBase::Play()
{
    const FLevelInfo2& SpawnInfo = PendingSpawns[currentIndex];
    if (CurrentTime >= SpawnInfo.SpawnTime)
    {
        UWorld* World = GetWorld();
        if (World && SpawnInfo.ActorClass)
        {
            FActorSpawnParameters Params;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            AActor* SpawnedActor = World->SpawnActor<AActor>(SpawnInfo.ActorClass, SpawnInfo.Location, SpawnInfo.Rotation, Params);
            if (SpawnedActor)
            {
                SpawnedActor->SetActorScale3D(SpawnInfo.Scale);
                SpawnedActor->SetActorHiddenInGame(false);

                float DestroyTime = SpawnInfo.SpawnTime + SpawnedActor->GetLifeSpan();
                if (TimeManager->CurrentTime >= DestroyTime)
                {
                    SpawnedActor->Destroy();
                }
            }
        }

        // 다음 액터를 스폰하기 위해 currentNodeIndex를 증가시킵니다.
        currentIndex++;
    }
}


