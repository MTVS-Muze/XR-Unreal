// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LoginGameMode.h"
#include "OSY_LoginWidget.h"


AOSY_LoginGameMode::AOSY_LoginGameMode()
{

}

void AOSY_LoginGameMode::BeginPlay()
{

    Super::BeginPlay();

    LoginUI = CreateWidget<UOSY_LoginWidget>(GetWorld(), LoginWidget);
    if (LoginUI != nullptr)
    {
        LoginUI->AddToViewport();

    }
}
