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


    LoadJsonData();
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

    for (int32 i = PendingSpawns.Num() - 1; i >= 0; --i)
    {
        const FActorSpawnInfo2& SpawnInfo = PendingSpawns[i];
        if (CurrentTime >= SpawnInfo.SpawnTime)
        {
            // 액터를 생성합니다.
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

            // 생성한 액터의 정보는 리스트에서 제거합니다.
            PendingSpawns.RemoveAt(i);
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
    FString LoadPath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");

    FString JsonString;
    if (FFileHelper::LoadFileToString(JsonString, *LoadPath))
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            if (JsonObject->HasField(TEXT("Locations")) && JsonObject->HasField(TEXT("Rotations")) && JsonObject->HasField(TEXT("Scales")) && JsonObject->HasField(TEXT("ActorClasses")) && JsonObject->HasField(TEXT("SpawnTime")))
            {
                TArray<TSharedPtr<FJsonValue>> LocationsArray = JsonObject->GetArrayField(TEXT("Locations"));
                TArray<TSharedPtr<FJsonValue>> RotationsArray = JsonObject->GetArrayField(TEXT("Rotations"));
                TArray<TSharedPtr<FJsonValue>> ScalesArray = JsonObject->GetArrayField(TEXT("Scales"));
                TArray<TSharedPtr<FJsonValue>> ActorClassesArray = JsonObject->GetArrayField(TEXT("ActorClasses"));
                TArray<TSharedPtr<FJsonValue>> SpawnTimeArray = JsonObject->GetArrayField(TEXT("SpawnTime"));

                for (int i = 0; i < LocationsArray.Num(); i++)
                {
                    TSharedPtr<FJsonObject> LocationObj = LocationsArray[i]->AsObject();
                    TSharedPtr<FJsonObject> RotationObj = RotationsArray[i]->AsObject();
                    TSharedPtr<FJsonObject> ScaleObj = ScalesArray[i]->AsObject();

                    FVector LoadedLocation(LocationObj->GetNumberField(TEXT("X")), LocationObj->GetNumberField(TEXT("Y")), LocationObj->GetNumberField(TEXT("Z")));
                    FRotator LoadedRotation(RotationObj->GetNumberField(TEXT("Pitch")), RotationObj->GetNumberField(TEXT("Yaw")), RotationObj->GetNumberField(TEXT("Roll")));
                    FVector LoadedScale(ScaleObj->GetNumberField(TEXT("X")), ScaleObj->GetNumberField(TEXT("Y")), ScaleObj->GetNumberField(TEXT("Z")));

                    FString ActorClassName = ActorClassesArray[i]->AsString();
                    UClass* ActorClass = FindObject<UClass>(ANY_PACKAGE, *ActorClassName);

                    float SavedTime = SpawnTimeArray[i]->AsNumber();

                    FActorSpawnInfo2 SpawnInfo;
                    SpawnInfo.Location = LoadedLocation;
                    SpawnInfo.Rotation = LoadedRotation;
                    SpawnInfo.Scale = LoadedScale;
                    SpawnInfo.ActorClass = ActorClass;
                    SpawnInfo.SpawnTime = SavedTime;

                    PendingSpawns.Add(SpawnInfo);
                }
            }
        }
    }
}



