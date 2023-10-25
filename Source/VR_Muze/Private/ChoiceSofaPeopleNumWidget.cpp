// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceSofaPeopleNumWidget.h"

void UChoiceSofaPeopleNumWidget::NativeConstruct()
{
	//btn_Back->OnClicked.AddDynamic(this,)
}

void UChoiceSofaPeopleNumWidget::SwitchCanvas(int32 index)
{

}

void UChoiceSofaPeopleNumWidget::OnSliderMoved(float value)
{
}

void UChoiceSofaPeopleNumWidget::OnClickNextButton(int32 index)
{
}



//인덱스 1번은 1명, 2번은 2명, 3번은 3명, 4번은 4명으로 제한된다.
//인덱스 1번을 고르면 1명의 자리배치로 자동으로 방이 만들어진다.
//인덱스 2번을 고르면 2명의 자리배치를 고를 수 있는 위젯이 나온다.
//인덱스 3번을 고르면 3명의 자리배치를 고를 수 있는 위젯이 나온다.
//인덱스 4번을 고르면 4명의 자리배치를 고를 수 있는 위젯이 나온다.
