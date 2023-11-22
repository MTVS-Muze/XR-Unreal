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
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "OSY_HttpRequestActor.h"
#include "ModeSelectGameModeBase.h"


void UMediaLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gm =GetWorld()->GetAuthGameMode<AKJS_GameModeBase>();
	gi = Cast<UOSY_GameInstance>(GetGameInstance());
	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

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
	btn_Single->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateSingleRoom);
	btn_Multi->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateRoom);
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
	btn_LeftSocial->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnCheckedbtn_LeftSocial);
	btn_RightSocial->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnCheckedbtn_RightSocial);



	/////////////////////////////////////////////////////////////////////////////////////////////
	btn_JoinSession->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_JoinSession);
	btn_CreateSession->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_CreateSession);
	btn_Back1->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Back1);

	/////////////////////////////////////////////////////////////////////////////////////////////
	btn_Count2->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Count2);
	btn_Back2->OnClicked.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Back2);
	
	Check_DoubleSit1->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedDoubleSit1);
	Check_DoubleSit2->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedDoubleSit2);
	
	if(gi)
	{
		btn_CreateDouble->OnClicked.AddDynamic(this, &UMediaLobbyWidget::CreateDoubleRoom);
	}

	player = Cast<AMyCharacter>(GetOwningPlayerPawn());

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

	if(MapName == "Box_indoor_Single")

	{
		FName LevelName = "2_LobbyMap";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}

	else if (MapName == "Box_indoor_Multi")
	{
		FName LevelName = "Box_indoor_Single";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}
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
	HttpActor->SendRequest(gi->AllMap);
	if (!gm->AllLevelArray.IsEmpty())
	{
		SetWidgetText(idnum);
	}
}
#pragma region Social
void UMediaLobbyWidget::OnClickedbtn_UpSocial()
{
	SwitchCanvasCategory(0);
}

void UMediaLobbyWidget::OnClickedbtn_DownSocial()
{
	SwitchCanvasCategory(2);
}

void UMediaLobbyWidget::OnCheckedbtn_LeftSocial()
{
	// 데이터 불러와
	idnum++;
	SetWidgetText(idnum);
}

void UMediaLobbyWidget::OnCheckedbtn_RightSocial()
{
	// 데이터 불러와
	idnum--;
	SetWidgetText(idnum);
}
#pragma endregion 

void UMediaLobbyWidget::OnClickedbtn_Back1()
{
	SwitchCanvas(0);
}

void UMediaLobbyWidget::OnClickedbtn_JoinSession()
{
	if (gi)
	{
		gi->FindOtherSession();
	}
}

void UMediaLobbyWidget::OnClickedbtn_CreateSession()
{
	SwitchCanvas(2);
}


void UMediaLobbyWidget::OnClickedbtn_Count2()
{
	SwitchCanvas(3);
}


void UMediaLobbyWidget::OnClickedbtn_Back2()
{
	SwitchCanvas(1);
}


void UMediaLobbyWidget::CreateSingleRoom()
{
	FName LevelName = "StreetCar_Play";
	
	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
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


void UMediaLobbyWidget::SetWidgetText(int id)
{
	FText IDText = FText::AsNumber(gm->AllLevelArray[id].Id);
	text_ID->SetText(IDText);

	FText TitleText = FText::FromString(gm->AllLevelArray[id].Title);
	text_Title->SetText(TitleText);

	FText SingerText = FText::FromString(gm->AllLevelArray[id].Singer);
	text_Singer->SetText(SingerText);

	FText ArtistText = FText::FromString(gm->AllLevelArray[id].MemberName);
	text_Artist->SetText(ArtistText);

	FText InfoText = FText::FromString(gm->AllLevelArray[id].Info);
	text_Info->SetText(InfoText);
}

void UMediaLobbyWidget::CreateDoubleRoom()
{
	if (gi)
	{
		gi->CheckboxStates.Add("Check_DoubleSit1", Check_DoubleSit1->GetCheckedState());
		gi->CheckboxStates.Add("Check_DoubleSit2", Check_DoubleSit2->GetCheckedState());
		gi->CreateMuzeSession(4);
	}

	if (Check_DoubleSit1->GetCheckedState() != ECheckBoxState::Checked && Check_DoubleSit2->GetCheckedState() != ECheckBoxState::Checked)
	{
		UE_LOG(LogTemp, Warning, TEXT("At least one checkbox should be checked."));
		return;
	}

	if (Check_DoubleSit1->GetCheckedState() == ECheckBoxState::Checked)
	{
		FName LevelName = "Box_indoor_Multi";
		// 레벨 로드 후 호출될 함수를 바인딩
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

	}

	else if (Check_DoubleSit2->GetCheckedState() == ECheckBoxState::Checked)
	{
		FName LevelName = "Box_indoor_Multi";
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}
}


