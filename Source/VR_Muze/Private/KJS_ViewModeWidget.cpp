// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_ViewModeWidget.h"
#include "Components/WidgetSwitcher.h"

void UKJS_ViewModeWidget::NativeConstruct()
{

}

void UKJS_ViewModeWidget::SwitchIndex(int32 index)
{
	ws_UISwitch->SetActiveWidgetIndex(index);

	
}
