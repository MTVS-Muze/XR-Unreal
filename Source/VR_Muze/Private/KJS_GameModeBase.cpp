// Fill out your copyright notice in the Description page of Project Settings.

#include "KJS_GameModeBase.h"
#include "OSY_GameInstance.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "MyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"


void AKJS_GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

}

void AKJS_GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            ULevelSequencePlayer* LevelSequencePlayer = SeqActor->GetSequencePlayer();

            FLevelSequenceCameraSettings CameraSettings;
            LevelSequencePlayer->Initialize(SeqActor->GetSequence(), GetWorld()->GetCurrentLevel(), CameraSettings);

            // 'OnFinished' 델리게이트에 바인딩 합니다.
            LevelSequencePlayer->OnFinished.AddDynamic(this, &AKJS_GameModeBase::OnLevelSequenceFinished);

            LevelSequencePlayer->Play();
        }
    }
}

void AKJS_GameModeBase::OnLevelSequenceFinished()
{
    FName LevelName = "Box_indoor_Multi";

    UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}
