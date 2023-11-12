// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaLobbyWidget.h"
#include "Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "KJS_BoxSofa.h"
#include "OSY_GameInstance.h"
#include "KJS_TypeInviteNumWidget.h"
#include "MyCharacter.h"
#include "Components/WidgetComponent.h"
#include "KJS_Box.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "EngineUtils.h"
#include "KJS_GameModeBase.h"


void UMediaLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	//MediaBox= Cast<AKJS_Box>(UGameplayStatics::)
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Canvas_Original
	List.Add(btn_SuperShy);
	List.Add(btn_Song2);
	List.Add(btn_Song3);
	List.Add(btn_Song4);
	List.Add(btn_Song5);
	List.Add(btn_Song6);
	List.Add(btn_Song7);
	List.Add(btn_Song8);
	List.Add(btn_Song9);
	List.Add(btn_Song10);

	btn_BackMain->OnClicked.AddDynamic(this, &UMediaLobbyWidget::BackSelectMode);
	btn_Multi->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateRoom);
	btn_Single->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateSingleRoom);
	btn_LeftOriginal->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Left);
	btn_RightOriginal->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Right);
	btn_UpOriginal->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_UpOriginal);
	btn_DownOriginal->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_DownOriginal);

	/////////////////////////////////////////////////////////////////////////////////////////////
	//Canvas_Social
	ListSocial.Add(btn_SuperShySocial);
	ListSocial.Add(btn_Song2Social);
	ListSocial.Add(btn_Song3Social);
	ListSocial.Add(btn_Song4Social);
	ListSocial.Add(btn_Song5Social);
	ListSocial.Add(btn_Song6Social);
	ListSocial.Add(btn_Song7Social);
	ListSocial.Add(btn_Song8Social);
	ListSocial.Add(btn_Song9Social);
	ListSocial.Add(btn_Song10Social);

	btn_UpSocial->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_UpSocial);
	btn_DownSocial->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_DownSocial);


	/////////////////////////////////////////////////////////////////////////////////////////////
	slider_playerCount->OnValueChanged.AddDynamic(this, &UMediaLobbyWidget::OnSliderMoved);
	btn_Next->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickNextButton);
	btn_Back->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickBackButton);
	btn_BackSingle->OnClicked.AddDynamic(this, &UMediaLobbyWidget::BackMakingRoom);
	btn_CreateSingle->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateSingleRoom);
	Check_SingleSit1->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedSignleSit1);
	Check_SingleSit2->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedSingleSit2);
	
	Check_DoubleSit1->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedDoubleSit1);
	Check_DoubleSit2->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedDoubleSit2);
	
	if(gi)
	{
		btn_CreateDouble->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateDoubleRoom);
	}

	player = Cast<AMyCharacter>(GetOwningPlayerPawn());

	UKJS_TypeInviteNumWidget* inviteWidget = Cast<UKJS_TypeInviteNumWidget>(player->ShowHostCodeWidget->GetWidget());

	UE_LOG(LogTemp, Warning, TEXT("GI value: %s"), *gi->GetInviteCode());

	if (inviteWidget != nullptr && gi->GetInviteCode() != "")
	{
		inviteWidget->text_InviteCode->SetText(FText::FromString(gi->GetInviteCode()));
		UE_LOG(LogTemp, Warning, TEXT("Widget post value: %s"), *inviteWidget->text_InviteCode->GetText().ToString());
	}
}

void UMediaLobbyWidget::SwitchCanvas(int32 index)
{
	ws_Switcher->SetActiveWidgetIndex(index);
}

void UMediaLobbyWidget::SwitchCanvasCategory(int32 index)
{
	ws_CategorySwitcher->SetActiveWidgetIndex(index);
}

void UMediaLobbyWidget::BackSelectMode()
{
	//StartLevel로 돌아가기

	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if(MapName == "Yellow_Single")

	{
		FName LevelName = "2_LobbyMap";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}

	else if (MapName == "Yellow_Multi")
	{
		FName LevelName = "Yellow_Single";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}

	UE_LOG(LogTemp, Warning, TEXT("PleaseGo"));

}

void UMediaLobbyWidget::JoinRoom()
{
	//방입장하기

}

void UMediaLobbyWidget::CreateRoom()
{
	//방만들기
	SwitchCanvas(1);
}

void UMediaLobbyWidget::OnClickedbtn_Left()
{

}

void UMediaLobbyWidget::OnClickedbtn_Right()
{

}

void UMediaLobbyWidget::OnClickedbtn_UpOriginal()
{
	SwitchCanvasCategory(2);
}

void UMediaLobbyWidget::OnClickedbtn_DownOriginal()
{
	SwitchCanvasCategory(1);
}

void UMediaLobbyWidget::OnClickedbtn_UpSocial()
{
	SwitchCanvasCategory(0);
}

void UMediaLobbyWidget::OnClickedbtn_DownSocial()
{
	SwitchCanvasCategory(2);
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

void UMediaLobbyWidget::OnCheckedSignleSit1(bool bIsChcecked)
{
	bIsChcecked = (Check_SingleSit1->GetCheckedState() == ECheckBoxState::Checked);

	if (bIsChcecked)
	{
		Check_SingleSit2->SetIsChecked(false);
	}
}

void UMediaLobbyWidget::OnCheckedSingleSit2(bool bIsChcecked)
{
	bIsChcecked = (Check_SingleSit2->GetCheckedState() == ECheckBoxState::Checked);

	if (bIsChcecked)
	{
		Check_SingleSit1->SetIsChecked(false);
	}
}

void UMediaLobbyWidget::CreateSingleRoom()
{

// 	AKJS_GameModeBase* GameMode = Cast<AKJS_GameModeBase>(GetWorld()->GetAuthGameMode());
// 	if (GameMode != nullptr)
// 	{
// 		GameMode->PlaySequence();
// 	}

	FName LevelName = "StreetCar_Play";
	
	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	

	//if (gi)
	//{
	//	//gi->Sit1CheckState = CheckState;
	//	gi->CheckboxStates.Add("Check_SingleSit1", Check_SingleSit1->GetCheckedState());
	//	gi->CheckboxStates.Add("Check_SingleSit2", Check_SingleSit2->GetCheckedState());
	//}

	////ECheckBoxState CheckState = Check_SingleSit1->GetCheckedState();
	//if (Check_SingleSit1->GetCheckedState() != ECheckBoxState::Checked && Check_SingleSit2->GetCheckedState() != ECheckBoxState::Checked)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("At least one checkbox should be checked."));
	//	return;
	//}
	//
	//if (Check_SingleSit1->GetCheckedState() == ECheckBoxState::Checked)
	//{
	//	FName LevelName = "Yellow_Multi";
	//
	//	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	//
	//}
	//
	//
	//else if (Check_SingleSit2->GetCheckedState() == ECheckBoxState::Checked)
	//{
	//	FName LevelName = "Yellow_Multi";
	//
	//	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	//}
}


void UMediaLobbyWidget::OnCheckedDoubleSit1(bool bIsChcecked)
{
	bIsChcecked = (Check_DoubleSit1->GetCheckedState() == ECheckBoxState::Checked);

	if (bIsChcecked)
	{
		Check_DoubleSit2->SetIsChecked(false);
	}
}

void UMediaLobbyWidget::OnCheckedDoubleSit2(bool bIsChcecked)
{
	bIsChcecked = (Check_DoubleSit2->GetCheckedState() == ECheckBoxState::Checked);

	if (bIsChcecked)
	{
		Check_DoubleSit1->SetIsChecked(false);
	}
}

void UMediaLobbyWidget::CreateDoubleRoom()
{
	if (gi)
	{
		gi->CheckboxStates.Add("Check_DoubleSit1", Check_DoubleSit1->GetCheckedState());
		gi->CheckboxStates.Add("Check_DoubleSit2", Check_DoubleSit2->GetCheckedState());
		RoomCode = gi->GenerateRandomCode(5);
		FName SessionName = FName(*RoomCode);
		gi->CreateMuzeSession((int32)slider_playerCount->GetValue(), SessionName);

	}

	if (Check_DoubleSit1->GetCheckedState() != ECheckBoxState::Checked && Check_DoubleSit2->GetCheckedState() != ECheckBoxState::Checked)
	{
		UE_LOG(LogTemp, Warning, TEXT("At least one checkbox should be checked."));
		return;
	}

	if (Check_DoubleSit1->GetCheckedState() == ECheckBoxState::Checked)
	{
		FName LevelName = "Yellow_Multi";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

	}


	else if (Check_DoubleSit2->GetCheckedState() == ECheckBoxState::Checked)
	{
		FName LevelName = "Yellow_Multi";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}
}