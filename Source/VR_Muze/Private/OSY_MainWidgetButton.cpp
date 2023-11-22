// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_MainWidgetButton.h"


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
