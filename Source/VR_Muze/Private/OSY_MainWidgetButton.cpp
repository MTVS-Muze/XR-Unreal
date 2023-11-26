// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_MainWidgetButton.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ButtonSlot.h"
#include "Runtime/UMG/Public/Components/SizeBoxSlot.h"


void UOSY_MainWidgetButton::SetButtonSize(FVector2D ButtonSize)
{
/*	USizeBoxSlot* ButtonSlot = Cast<USizeBoxSlot>(Slot);
	if (ButtonSlot)
	{
		ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		ButtonSlot->SetSize(ButtonSize);
	}
	-*/
}

void UOSY_MainWidgetButton::SetId(int ID)
{
	LevelDataID=ID;
}

int UOSY_MainWidgetButton::GetID()
{
	return LevelDataID;
}

void UOSY_MainWidgetButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnClicked.AddDynamic(this, &UOSY_MainWidgetButton::OnButtonClicked);
}

void UOSY_MainWidgetButton::OnButtonClicked()
{
	if (LevelDataID)
	{
		OnButtonClickedDelegate.Broadcast(LevelDataID);
	}
}

