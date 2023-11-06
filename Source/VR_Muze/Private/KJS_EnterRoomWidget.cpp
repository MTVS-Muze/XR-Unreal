// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_EnterRoomWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableText.h"

void UKJS_EnterRoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	btn_Enter->OnClicked.AddDynamic(this, &UKJS_EnterRoomWidget::OnEnterClicked);
	
}

void UKJS_EnterRoomWidget::OnEnterClicked()
{
	if (edit_EnterRoomCode)
	{
		FString RoomCode = edit_EnterRoomCode->GetText().ToString();
	}
}
