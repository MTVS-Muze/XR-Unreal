// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_GameInstance.h"
#include "Components/CanvasPanel.h" 
#include "HeadMountedDisplayFunctionLibrary.h"
#include "IXRTrackingSystem.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_MediaEnter->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonMedia);
	btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonSwitchCreative);
	btn_CreativeEnter->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreativeMode);
	btn_BackModeSelect->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonBackModeSelect);
	btn_CreateBox->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreateBox);
	btn_Create->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreateEnd);
	btn_BackBoxList->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonBackBoxList);
	btn_HiddenErrorUI->OnClicked.AddDynamic(this, &UMainWidget::OnClickedHiddenErrorUI);

	if (ErrorUI)
	{
		ErrorUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainWidget::SwitchCanvas(int32 index)
{
	ws_UISwitch->SetActiveWidgetIndex(index);
}

void UMainWidget::OnClickedButtonMedia()
{
	
	if (GEngine->XRSystem.IsValid())
	{
		FName LevelName = "Yellow_Single";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}

	else
	{
		ErrorUI->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::OnClickedButtonSwitchCreative()
{
	SwitchCanvas(1);
}

void UMainWidget::OnClickedButtonCreativeMode()
{
	SwitchCanvas(2);

}

void UMainWidget::OnClickedHiddenErrorUI()
{
	if (ErrorUI)
	{
		ErrorUI->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UMainWidget::OnClickedButtonBackModeSelect()
{
	SwitchCanvas(2);
}

void UMainWidget::OnClickedButtonCreateBox()
{
	SwitchCanvas(2);
}

void UMainWidget::OnClickedButtonCreateEnd()
{
	//SwitchCanvas(2);

	FName LevelName = "3_CreativeMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UMainWidget::OnClickedButtonBackBoxList()
{
	SwitchCanvas(2);
}
