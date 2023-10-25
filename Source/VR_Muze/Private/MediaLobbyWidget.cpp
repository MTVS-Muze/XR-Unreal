// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaLobbyWidget.h"
#include "Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"

void UMediaLobbyWidget::NativeConstruct()
{
	btn_BackMain->OnClicked.AddDynamic(this, &UMediaLobbyWidget::BackSelectMode);
	btn_Join->OnClicked.AddDynamic(this, &UMediaLobbyWidget::JoinRoom);
	btn_CreateRoom->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateRoom);
}

void UMediaLobbyWidget::SwitchCanvas(int32 index)
{
	ws_Switcher->SetActiveWidgetIndex(index);
}

void UMediaLobbyWidget::BackSelectMode()
{
	//StartLevel�� ���ư���

	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

	UE_LOG(LogTemp, Warning, TEXT("PleaseGo"));

}

void UMediaLobbyWidget::JoinRoom()
{
	//�������ϱ�

}

void UMediaLobbyWidget::CreateRoom()
{
	//�游���
	SwitchCanvas(1);
}

void UMediaLobbyWidget::OnSliderMoved(float value)
{
}

void UMediaLobbyWidget::OnClickNextButton(int32 index)
{
}


