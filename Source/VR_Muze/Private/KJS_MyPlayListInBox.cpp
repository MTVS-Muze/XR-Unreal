// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_MyPlayListInBox.h"
#include "Components/Button.h"

void UKJS_MyPlayListInBox::NativeConstruct()
{
	btn_ListBack->OnClicked.AddDynamic(this, &UKJS_MyPlayListInBox::PlayBack);
	btn_Play->OnClicked.AddDynamic(this, &UKJS_MyPlayListInBox::PlayMedia);
	btn_Stop->OnClicked.AddDynamic(this, &UKJS_MyPlayListInBox::StopMedia);
	btn_ListFront->OnClicked.AddDynamic(this, &UKJS_MyPlayListInBox::PlayFrontMedia);
}

void UKJS_MyPlayListInBox::PlayBack()
{

}

void UKJS_MyPlayListInBox::PlayMedia()
{

}

void UKJS_MyPlayListInBox::StopMedia()
{

}

void UKJS_MyPlayListInBox::PlayFrontMedia()
{

}
