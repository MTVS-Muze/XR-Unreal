// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_SequenceWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "OSY_PropWidget.h"
#include "OSY_CreativeGameModeBase.h"
#include "OSY_TImeActor.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UOSY_SequenceWidget::NativeConstruct()
{
	Super::NativeConstruct();

    gm = GetWorld()->GetAuthGameMode<AOSY_CreativeGameModeBase>();

    TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));

    if (sl_TimeStaff)
    {
        sl_TimeStaff->OnValueChanged.AddDynamic(this, &UOSY_SequenceWidget::HandleSliderValueChanged);
        sl_TimeStaff->OnMouseCaptureBegin.AddDynamic(this, &UOSY_SequenceWidget::HandleSliderMouseCaptureBegin);
        sl_TimeStaff->OnMouseCaptureEnd.AddDynamic(this, &UOSY_SequenceWidget::HandleSliderMouseCaptureEnd);
    }

#pragma region Button
    btn_Play->OnClicked.AddDynamic(this, &UOSY_SequenceWidget::SequencePlay);
    btn_Pause->OnClicked.AddDynamic(this, &UOSY_SequenceWidget::SequencePause);
    btn_Stop->OnClicked.AddDynamic(this, &UOSY_SequenceWidget::SequenceStop);
#pragma endregion


    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOSY_SequenceWidget::LoadJsonData, 2.0f, false);
}

void UOSY_SequenceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

    CurrentTime = TimeManager->CurrentTime;
    UE_LOG(LogTemp,Warning,TEXT("%f"),CurrentTime);

    if (CurrentTime <= MaxTime)
    {
        if (TimeManager->bShouldTick)
        {
            UpdateProgressBar();
        }
    }

    if (currentIndex >= PendingSpawns.Num())
    {
        return;
    }

    const FLevelInfo& SpawnInfo = PendingSpawns[currentIndex];
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

void UOSY_SequenceWidget::UpdateProgressBar() const
{

    const float Progress = CurrentTime / MaxTime;

    if (sl_TimeStaff)
    {
        sl_TimeStaff->SetMaxValue(MaxTime);
        sl_TimeStaff->SetValue(CurrentTime);
    }


}

void UOSY_SequenceWidget::HandleSliderValueChanged(float Value)
{
    CorrespondingTime = Value * MaxTime;
    tempValue=Value;
}


void UOSY_SequenceWidget::HandleSliderMouseCaptureBegin()
{

}

void UOSY_SequenceWidget::HandleSliderMouseCaptureEnd()
{
   TimeManager->CurrentTime = tempValue;
}

void UOSY_SequenceWidget::SequencePlay()
{
    TimeManager->bShouldTick = true;

    if (AudioComponent != nullptr)
    {
        AudioComponent->Stop();
    }
    Song=gm->Song;
    AudioComponent = UGameplayStatics::SpawnSound2D(this, Song,1,1,CurrentTime);
}

void UOSY_SequenceWidget::SequencePause()
{
    UE_LOG(LogTemp, Warning, TEXT("SequencePause"));
    
    TimeManager->bShouldTick = false;

    if (AudioComponent != nullptr)
    {
        AudioComponent->FadeOut(0.1f, 0.0f);
    }
    
}

void UOSY_SequenceWidget::SequenceStop()
{
    UE_LOG(LogTemp, Warning, TEXT("SequenceStop"));
    TimeManager->bShouldTick = false;
    TimeManager->CurrentTime = 0;

    if (AudioComponent != nullptr)
    {
        AudioComponent->Stop();
    }
}

void UOSY_SequenceWidget::LoadJsonData()
{

    // gm에 있는 데이터를 PendingSpawns에 추가한다.


    for (int i = 0; i < gm->Locations.Num(); i++)
    {
        FLevelInfo pendingSpawn;
        pendingSpawn.Location = gm->Locations[i];
        pendingSpawn.Rotation = gm->Rotations[i];
        pendingSpawn.Scale = gm->Scales[i];


        FString BlueprintName = gm->ActorClasses[i];
        BlueprintName = BlueprintName.Replace(TEXT("_C"), TEXT(""));
        FString BlueprintHame= gm->ActorClasses[i];
        FString BlueprintPath = FString::Printf(TEXT("/Game/DEV/OOSY/Blueprints/BP_Niagara/%s.%s"), *BlueprintName, *BlueprintHame);
        

        UClass* ActorClass = LoadObject<UClass>(nullptr, *BlueprintPath);
        pendingSpawn.ActorClass = ActorClass;

        pendingSpawn.SpawnTime = gm->SpawnTimes[i];
        pendingSpawn.LifeSpan = gm->LifeSpans[i];

        PendingSpawns.Add(pendingSpawn);


    }


}



