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

    

    //FTimerHandle TimerHandle;
    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AKJS_GameModeBase::OnLevelSequenceEnd, 10.0f, false);
}

void AKJS_GameModeBase::BeginPlay()
{
    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            // ���� �������� ����Ѵ�.
            SeqActor->SequencePlayer->Play();
            SeqActor->SequencePlayer->OnFinished.AddDynamic(this, &AKJS_GameModeBase::OnLevelSequenceEnd);
        }
    }
}

void AKJS_GameModeBase::OnLevelSequenceEnd()
{
    
    // Default Pawn�� �����մϴ�.
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (PC && !PC->GetPawn())
        {
            RestartPlayer(PC);
            if (PC->GetPawn() == nullptr)
            {
                UE_LOG(LogTemp, Warning, TEXT("Character was not created correctly."));
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Character is created and possessed."));
                PC->Possess(PC->GetPawn());
            }
        }
    }
}
