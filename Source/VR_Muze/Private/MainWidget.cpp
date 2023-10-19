// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"

void UMainWidget::NativeConstruct()
{

	btn_Media->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonMedia);
	btn_Creative->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreativeMode);
	btn_BackModeSelect->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonBackModeSelect);
	btn_CreateBox->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreateBox);
	btn_Create->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreateEnd);
	btn_BackBoxList->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonBackBoxList);
}

void UMainWidget::SwitchCanvas(int32 index)
{
	ws_UISwitch->SetActiveWidgetIndex(index);
}

void UMainWidget::OnClickedButtonMedia()
{

}

void UMainWidget::OnClickedButtonCreativeMode()
{
	SwitchCanvas(1);
}

void UMainWidget::OnClickedButtonBackModeSelect()
{
	SwitchCanvas(0);
}

void UMainWidget::OnClickedButtonCreateBox()
{
	SwitchCanvas(2);
}

void UMainWidget::OnClickedButtonCreateEnd()
{
	//SwitchCanvas(2);
}

void UMainWidget::OnClickedButtonBackBoxList()
{
	SwitchCanvas(1);
}
