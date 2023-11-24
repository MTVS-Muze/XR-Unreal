// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_CustomizeGameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "OSY_MYinfoWidget.h"
#include "Components/Image.h"
#include "OSY_GameInstance.h"
#include "Runtime/Engine/Public/ImageUtils.h"

void AKJS_CustomizeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    gi = Cast<UOSY_GameInstance>(GetGameInstance());

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

    MyInfoUI = CreateWidget<UOSY_MyInfoWidget>(GetWorld(), MyInfoWidget);
    if (MyInfoUI != nullptr)
    {
        MyInfoUI->AddToViewport();
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

void AKJS_CustomizeGameModeBase::SetImage(class UTexture2D* tex)
{
    if (MyInfoUI != nullptr)
    {
        MyInfoUI->img_profile->SetBrushFromTexture(tex);
    }
}
