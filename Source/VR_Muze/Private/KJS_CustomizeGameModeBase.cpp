// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_CustomizeGameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"

void AKJS_CustomizeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            SeqActor->SequencePlayer->OnFinished.AddDynamic(this, &AKJS_CustomizeGameModeBase::OnSequenceFinished);
            // 레벨 시퀀스를 재생한다.
            SeqActor->SequencePlayer->Play();
        }
    }
}

void AKJS_CustomizeGameModeBase::OnSequenceFinished()
{
    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            SeqActor->SequencePlayer->Play();
        }
    }
}
