// Fill out your copyright notice in the Description page of Project Settings.

#include "KJS_MediaListUI.h"
#include "Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UKJS_MediaListUI::NativeConstruct()
{
	btn_Play->OnClicked.AddDynamic(this,&UKJS_MediaListUI::TransferPlayMediaLevel);
}

void UKJS_MediaListUI::TransferPlayMediaLevel()
{
	FName LevelName = "MediaLobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}
