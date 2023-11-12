// Fill out your copyright notice in the Description page of Project Settings.


#include "ModeSelectGameModeBase.h"
#include "MainWidget.h"

AModeSelectGameModeBase::AModeSelectGameModeBase()
{

}

void AModeSelectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    ModeSelectUI = CreateWidget<UMainWidget>(GetWorld(), ModeSelectWidget);
    if (ModeSelectUI != nullptr)
    {
        ModeSelectUI->AddToViewport();

    }
}
