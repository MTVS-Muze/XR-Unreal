// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CustomGameMode.h"
#include "CharacterCustomizeWidget.h"
#include "OSY_GameInstance.h"
#include "OSY_HttpRequestActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AOSY_CustomGameMode::AOSY_CustomGameMode()
{

}

void AOSY_CustomGameMode::BeginPlay()
{

	Super::BeginPlay();


    CustomUI = CreateWidget<UCharacterCustomizeWidget>(GetWorld(), CustomWidget);
    if (CustomUI != nullptr)
    {
        CustomUI->AddToViewport();
    }

    gi = Cast<UOSY_GameInstance>(GetGameInstance());
    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

    HttpActor->SendRequest(gi->CustomURL);

}
