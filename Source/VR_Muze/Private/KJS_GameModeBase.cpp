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
#include "OSY_HttpRequestActor.h"


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
            SeqActor->SequencePlayer->Play();
        }
    }
    gi = Cast<UOSY_GameInstance>(GetGameInstance());

    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

    SendReq();
    
}

void AKJS_GameModeBase::SendReq()
{
    if (HttpActor != nullptr)
    {
      HttpActor->SendRequest(gi->AllMap);

    }

}

