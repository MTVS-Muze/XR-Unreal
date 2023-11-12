// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_StreetGameMode.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/MovieScene/Public/MovieSceneSequencePlaybackSettings.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"

AOSY_StreetGameMode::AOSY_StreetGameMode()
{

}

void AOSY_StreetGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlaySequence();

}

void AOSY_StreetGameMode::PlaySequence()
{
    FString SequencePath = TEXT("/Game/ocean/Streetcar.Streetcar");

    // 시퀀스 애셋 로드
    ULevelSequence* Sequence = LoadObject<ULevelSequence>(nullptr, *SequencePath);
    if (Sequence == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load sequence from %s"), *SequencePath);
        return;
    }

    // 시퀀스 플레이어 생성
    FMovieSceneSequencePlaybackSettings PlaybackSettings;
    ALevelSequenceActor* OutActor = nullptr;  // 새로운 레벨 시퀀스 액터를 생성하거나, 이미 존재하는 액터를 찾아서 사용하세요.
    ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, PlaybackSettings, OutActor);

    // 시퀀스 플레이 시작
    if (SequencePlayer != nullptr)
    {
        SequencePlayer->Play();
    }
}
