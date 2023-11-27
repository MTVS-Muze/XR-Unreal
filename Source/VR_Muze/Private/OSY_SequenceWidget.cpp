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
#include "OSY_GameInstance.h"
#include "Runtime/Core/Public/Templates/SharedPointer.h"
#include "OSY_HttpRequestActor.h"

void UOSY_SequenceWidget::NativeConstruct()
{
	Super::NativeConstruct();


    gi = Cast<UOSY_GameInstance>(GetGameInstance());
    gm = GetWorld()->GetAuthGameMode<AOSY_CreativeGameModeBase>();

    TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));
    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

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
    btn_Save->OnClicked.AddDynamic(this, &UOSY_SequenceWidget::SaveJsonData);
    btn_PostJson->OnClicked.AddDynamic(this, &UOSY_SequenceWidget::PostJSon);
#pragma endregion


    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOSY_SequenceWidget::LoadJsonData, 2.0f, false);

    tb_SongName->SetText(FText::FromString(gi->song));

   
}

void UOSY_SequenceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

    CurrentTime = TimeManager->CurrentTime;
    UE_LOG(LogTemp,Warning,TEXT("%f"),CurrentTime);

	int32 TotalSeconds = FMath::RoundToInt(CurrentTime);
	int32 Minutes = TotalSeconds / 60;
	int32 Seconds = TotalSeconds % 60;

	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	tb_Currentime->SetText(FText::FromString(TimeString));

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

        // ���� ���͸� �����ϱ� ���� currentNodeIndex�� ������ŵ�ϴ�.
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

    // gm�� �ִ� �����͸� PendingSpawns�� �߰��Ѵ�.


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

void UOSY_SequenceWidget::SaveJsonData()
{
    JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> LocationsArray;
	TArray<TSharedPtr<FJsonValue>> RotationsArray;
	TArray<TSharedPtr<FJsonValue>> ScalesArray;
	TArray<TSharedPtr<FJsonValue>> ActorClassesArray;
	TArray<TSharedPtr<FJsonValue>> SpawnTimeArray;
	TArray<TSharedPtr<FJsonValue>> LifeSpanArray;


	for (int i = 0; i < SavedLocations.Num(); i++)
	{
		TSharedPtr<FJsonObject> LocationObj = MakeShareable(new FJsonObject);
		LocationObj->SetNumberField(TEXT("X"), SavedLocations[i].X);
		LocationObj->SetNumberField(TEXT("Y"), SavedLocations[i].Y);
		LocationObj->SetNumberField(TEXT("Z"), SavedLocations[i].Z);
		LocationsArray.Add(MakeShareable(new FJsonValueObject(LocationObj)));

		TSharedPtr<FJsonObject> RotationObj = MakeShareable(new FJsonObject);
		RotationObj->SetNumberField(TEXT("Pitch"), SavedRotations[i].Pitch);
		RotationObj->SetNumberField(TEXT("Yaw"), SavedRotations[i].Yaw);
		RotationObj->SetNumberField(TEXT("Roll"), SavedRotations[i].Roll);
		RotationsArray.Add(MakeShareable(new FJsonValueObject(RotationObj)));

		TSharedPtr<FJsonObject> ScaleObj = MakeShareable(new FJsonObject);
		ScaleObj->SetNumberField(TEXT("X"), SavedScales[i].X);
		ScaleObj->SetNumberField(TEXT("Y"), SavedScales[i].Y);
		ScaleObj->SetNumberField(TEXT("Z"), SavedScales[i].Z);
		ScalesArray.Add(MakeShareable(new FJsonValueObject(ScaleObj)));

		ActorClassesArray.Add(MakeShareable(new FJsonValueString(SavedActorClasses[i]->GetName())));
		SpawnTimeArray.Add(MakeShareable(new FJsonValueNumber(SavedSpawnTimes[i])));
		LifeSpanArray.Add(MakeShareable(new FJsonValueNumber(SavedLifeSpans[i])));

	}

	JsonObject->SetArrayField(TEXT("Locations"), LocationsArray);
	JsonObject->SetArrayField(TEXT("Rotations"), RotationsArray);
	JsonObject->SetArrayField(TEXT("Scales"), ScalesArray);
	JsonObject->SetArrayField(TEXT("ActorClasses"), ActorClassesArray);
	JsonObject->SetArrayField(TEXT("SpawnTime"), SpawnTimeArray);
	JsonObject->SetArrayField(TEXT("LifeSpan"), LifeSpanArray);


	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	FString SavePath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");
	FFileHelper::SaveStringToFile(JsonString, *SavePath);
}

void UOSY_SequenceWidget::PostJSon()
{
    JsonObject = MakeShareable(new FJsonObject);

    TArray<TSharedPtr<FJsonValue>> LocationsArray;
    TArray<TSharedPtr<FJsonValue>> RotationsArray;
    TArray<TSharedPtr<FJsonValue>> ScalesArray;
    TArray<TSharedPtr<FJsonValue>> ActorClassesArray;
    TArray<TSharedPtr<FJsonValue>> SpawnTimeArray;
    TArray<TSharedPtr<FJsonValue>> LifeSpanArray;


    for (int i = 0; i < SavedLocations.Num(); i++)
    {
        TSharedPtr<FJsonObject> LocationObj = MakeShareable(new FJsonObject);
        LocationObj->SetNumberField(TEXT("X"), SavedLocations[i].X);
        LocationObj->SetNumberField(TEXT("Y"), SavedLocations[i].Y);
        LocationObj->SetNumberField(TEXT("Z"), SavedLocations[i].Z);
        LocationsArray.Add(MakeShareable(new FJsonValueObject(LocationObj)));

        TSharedPtr<FJsonObject> RotationObj = MakeShareable(new FJsonObject);
        RotationObj->SetNumberField(TEXT("Pitch"), SavedRotations[i].Pitch);
        RotationObj->SetNumberField(TEXT("Yaw"), SavedRotations[i].Yaw);
        RotationObj->SetNumberField(TEXT("Roll"), SavedRotations[i].Roll);
        RotationsArray.Add(MakeShareable(new FJsonValueObject(RotationObj)));

        TSharedPtr<FJsonObject> ScaleObj = MakeShareable(new FJsonObject);
        ScaleObj->SetNumberField(TEXT("X"), SavedScales[i].X);
        ScaleObj->SetNumberField(TEXT("Y"), SavedScales[i].Y);
        ScaleObj->SetNumberField(TEXT("Z"), SavedScales[i].Z);
        ScalesArray.Add(MakeShareable(new FJsonValueObject(ScaleObj)));

        ActorClassesArray.Add(MakeShareable(new FJsonValueString(SavedActorClasses[i]->GetName())));
        SpawnTimeArray.Add(MakeShareable(new FJsonValueNumber(SavedSpawnTimes[i])));
        LifeSpanArray.Add(MakeShareable(new FJsonValueNumber(SavedLifeSpans[i])));

    }

    JsonObject->SetArrayField(TEXT("Locations"), LocationsArray);
    JsonObject->SetArrayField(TEXT("Rotations"), RotationsArray);
    JsonObject->SetArrayField(TEXT("Scales"), ScalesArray);
    JsonObject->SetArrayField(TEXT("ActorClasses"), ActorClassesArray);
    JsonObject->SetArrayField(TEXT("SpawnTime"), SpawnTimeArray);
    JsonObject->SetArrayField(TEXT("LifeSpan"), LifeSpanArray);


    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

    JsonStringPost = JsonString;

    if (HttpActor != nullptr)
    {
        HttpActor->PostRequest(gi->PostMyMap, JsonStringPost);
    }

    UE_LOG(LogTemp, Warning, TEXT("json : %s"), *JsonStringPost);
}

