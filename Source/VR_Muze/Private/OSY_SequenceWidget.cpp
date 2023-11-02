// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_SequenceWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "OSY_PropWidget.h"
#include "OSY_CreativeGameModeBase.h"
#include "OSY_TImeActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UOSY_SequenceWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
    btn_Save->OnClicked.AddDynamic(this, &UOSY_SequenceWidget::SequenceSave);
#pragma endregion
   
}

void UOSY_SequenceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

    CurrentTime = TimeManager->CurrentTime;

    if (CurrentTime <= MaxTime)
    {
        if (TimeManager->bShouldTick)
        {
            UpdateProgressBar();

        }
    }
       
}

void UOSY_SequenceWidget::UpdateProgressBar() const
{

    const float Progress = CurrentTime / MaxTime;

    if (sl_TimeStaff)
    {
        sl_TimeStaff->SetMaxValue(MaxTime);
        sl_TimeStaff->SetValue(CurrentTime);
        //->SetValue(Progress);
    }

    if (TimeTextBlock)
    {
        const int32 Minutes = FMath::FloorToInt(CurrentTime / 60.0f);
        const int32 Seconds = FMath::FloorToInt(FMath::Fmod(CurrentTime, 60.0f));

        FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
        TimeTextBlock->SetText(FText::FromString(TimeString));
    }
}

void UOSY_SequenceWidget::HandleSliderValueChanged(float Value)
{
    CorrespondingTime = Value * MaxTime;
    tempValue=Value;
    UE_LOG(LogTemp, Warning, TEXT("Slider value changed: %f, corresponding time: %f"), Value, CorrespondingTime);
}



void UOSY_SequenceWidget::HandleSliderMouseCaptureBegin()
{
  // TimeManager->bShouldTick = false;

}

void UOSY_SequenceWidget::HandleSliderMouseCaptureEnd()
{
   TimeManager->CurrentTime = tempValue;
    //TimeManager->bShouldTick = true;
}

void UOSY_SequenceWidget::SequencePlay()
{
    UE_LOG(LogTemp, Warning, TEXT("SequencePlay"));
    TimeManager->bShouldTick = true;
    UE_LOG(LogTemp, Warning, TEXT("SequencePlayCurrent :%f"),TimeManager->CurrentTime);

}

void UOSY_SequenceWidget::SequencePause()
{
    UE_LOG(LogTemp, Warning, TEXT("SequencePause"));
    TimeManager->bShouldTick = false;
}

void UOSY_SequenceWidget::SequenceStop()
{
    UE_LOG(LogTemp, Warning, TEXT("SequenceStop"));
    TimeManager->bShouldTick = false;
    TimeManager->CurrentTime = 0;
}

void UOSY_SequenceWidget::SequenceSave()
{
    UE_LOG(LogTemp, Warning, TEXT("SequenceSave"));

}

