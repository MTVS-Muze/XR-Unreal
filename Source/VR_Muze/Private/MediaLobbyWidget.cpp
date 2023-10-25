// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaLobbyWidget.h"
#include "Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"

void UMediaLobbyWidget::NativeConstruct()
{
	btn_BackMain->OnClicked.AddDynamic(this, &UMediaLobbyWidget::BackSelectMode);
	btn_Join->OnClicked.AddDynamic(this, &UMediaLobbyWidget::JoinRoom);
	btn_CreateRoom->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateRoom);
	slider_playerCount->OnValueChanged.AddDynamic(this, &UMediaLobbyWidget::OnSliderMoved);
	btn_Next->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickNextButton);
	btn_Back->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickBackButton);
	btn_BackSingle->OnClicked.AddDynamic(this, &UMediaLobbyWidget::BackMakingRoom);
	btn_CreateSingle->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateSingleRoom);
	Check_Sit1->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedSit1);
	Check_Sit2->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedSit2);
	
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
	text_sliderCount->SetText(FText::AsNumber((int32)value));
}

void UMediaLobbyWidget::OnClickNextButton()
{
	int32 sliderValue = FMath::TruncToInt(slider_playerCount->GetValue());

	if (sliderValue == 1)
	{
		SwitchCanvas(2);
	}
	else if (sliderValue == 2)
	{
		SwitchCanvas(3);
	}
}

void UMediaLobbyWidget::OnClickBackButton()
{
	SwitchCanvas(0);
}

void UMediaLobbyWidget::BackMakingRoom()
{
	SwitchCanvas(1);
}

void UMediaLobbyWidget::OnCheckedSit1(bool bIsChcecked)
{
	bIsChcecked = (Check_Sit1->GetCheckedState() == ECheckBoxState::Checked);

	if (bIsChcecked)
	{
		Check_Sit2->SetIsChecked(false);
	}

	//Sit1�� Check�����̸� Sit2�� üũ���·� �ٲ��� ���Ѵ�.
	//Sit1�� Check���¿��� Create��ư�� ������ Box��� �̸��� ������ �̵��ϰ� ������ ���� ��ġ�� sit1�� Check�����϶� �ش��ϴ� Prop�� Box��� �̸��� ������ �����ȴ�.
}

void UMediaLobbyWidget::OnCheckedSit2(bool bIsChcecked)
{
	bIsChcecked = (Check_Sit2->GetCheckedState() == ECheckBoxState::Checked);

	if (bIsChcecked)
	{
		Check_Sit1->SetIsChecked(false);
	}
}

void UMediaLobbyWidget::CreateSingleRoom()
{


	if (Check_Sit1->GetCheckedState() == ECheckBoxState::Checked)
	{
		FName LevelName = "5_Box";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

		FActorSpawnParameters params;
		//AActor* Cube = GetWorld()->SpawnActor<AActor>(ACubeActor::StaticClass)
	}


	else if (Check_Sit2->GetCheckedState() == ECheckBoxState::Checked)
	{
		FName LevelName = "6_Box";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

		FActorSpawnParameters params;
		//AActor* Cube = GetWorld()->SpawnActor<AActor>(ACubeActor::StaticClass)
	}
}


