// Fill out your copyright notice in the Description page of Project Settings.

#include "KJS_GameModeBase.h"
#include "OSY_GameInstance.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "MyCharacter.h"


void AKJS_GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

}

void AKJS_GameModeBase::BeginPlay()
{
    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            // 레벨 시퀀스를 재생한다.
            SeqActor->SequencePlayer->Play();
        }
    }
}
