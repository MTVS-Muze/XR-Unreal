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

    // ������ �ּ� �ε�
    ULevelSequence* Sequence = LoadObject<ULevelSequence>(nullptr, *SequencePath);
    if (Sequence == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load sequence from %s"), *SequencePath);
        return;
    }

    // ������ �÷��̾� ����
    FMovieSceneSequencePlaybackSettings PlaybackSettings;
    ALevelSequenceActor* OutActor = nullptr;  // ���ο� ���� ������ ���͸� �����ϰų�, �̹� �����ϴ� ���͸� ã�Ƽ� ����ϼ���.
    ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, PlaybackSettings, OutActor);

    // ������ �÷��� ����
    if (SequencePlayer != nullptr)
    {
        SequencePlayer->Play();
    }
}
