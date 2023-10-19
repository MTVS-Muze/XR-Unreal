// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatedBoxInfo.h"
#include "Components/Button.h"

void UCreatedBoxInfo::NativeConstruct()
{
	btn_EnterLevel->OnClicked.AddDynamic(this, &UCreatedBoxInfo::EnterLevel);
}

void UCreatedBoxInfo::EnterLevel()
{

}
