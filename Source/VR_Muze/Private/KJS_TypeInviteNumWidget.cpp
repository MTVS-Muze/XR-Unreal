// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_TypeInviteNumWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "OSY_GameInstance.h"
#include "MediaLobbyWidget.h"

void UKJS_TypeInviteNumWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());
}

void UKJS_TypeInviteNumWidget::CreateInviteCode(const FString& InviteCode)
{
	UE_LOG(LogTemp,Warning,TEXT("What is Code : %s"),*InviteCode);
	UMediaLobbyWidget* MediaLobbyWidget = Cast<UMediaLobbyWidget>(GetOuter());

	text_InviteCode->SetText(FText::FromString(InviteCode));

}
