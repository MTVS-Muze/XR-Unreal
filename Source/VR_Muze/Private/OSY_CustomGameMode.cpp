// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_CustomGameMode.h"
#include "CharacterCustomizeWidget.h"

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

}
