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
#include "OSY_MainWidgetButton.h"
#include "KJS_MultiGameModeBase.h"


void UMediaLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bHasExecuted = false;

	
	
	gm =GetWorld()->GetAuthGameMode<AKJS_GameModeBase>();
	Multigm = GetWorld()->GetAuthGameMode<AKJS_MultiGameModeBase>();
	
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

	btn_BackMain->OnPressed.AddDynamic(this, &UMediaLobbyWidget::BackSelectMode);
	btn_Single->OnPressed.AddDynamic(this, &UMediaLobbyWidget::CreateSingleRoom);
	btn_Multi->OnPressed.AddDynamic(this, &UMediaLobbyWidget::CreateRoom);
	btn_LeftOriginal->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Left);
	btn_RightOriginal->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Right);
	btn_UpOriginal->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_UpOriginal);
	btn_DownOriginal->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_DownOriginal);

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

	btn_UpSocial->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_UpSocial);
	btn_DownSocial->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_DownSocial);
	btn_LeftSocial->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnCheckedbtn_LeftSocial);
	btn_RightSocial->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnCheckedbtn_RightSocial);

	/////////////////////////////////////////////////////////////////////////////////////////////
	btn_JoinSession->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_JoinSession);
	btn_CreateSession->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_CreateSession);
	btn_Back1->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Back1);

	/////////////////////////////////////////////////////////////////////////////////////////////
	btn_Count2->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Count2);
	btn_Back2->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_Back2);
	btn_BackDouble->OnPressed.AddDynamic(this, &UMediaLobbyWidget::OnClickedbtn_BackDouble);
	
	Check_DoubleSit1->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedDoubleSit1);
	Check_DoubleSit2->OnCheckStateChanged.AddDynamic(this, &UMediaLobbyWidget::OnCheckedDoubleSit2);

	btn_socialPlay->OnPressed.AddDynamic(this, &UMediaLobbyWidget::SetID);
	
	if(gi)
	{
		btn_CreateDouble->OnPressed.AddDynamic(this, &UMediaLobbyWidget::CreateDoubleRoom);
	}

	player = Cast<AMyCharacter>(GetOwningPlayerPawn());

	int32 InitialCanvasIndex = 0;

	// 버튼 가시성 업데이트
	UpdateButtonVisibility(InitialCanvasIndex);



	if (gm && gm->AllLevelArray.Num() > 0)
	{
		idnum = gm->AllLevelArray[0].Id;
	}
	else
	{
		// 배열이 비어있거나 null일 때 처리하려는 로직을 여기에 작성하실 수 있습니다.
		UE_LOG(LogTemp, Warning, TEXT("AllLevelArray is empty or not initialized."));
		return;
	}

}

void UMediaLobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);
	// 만약 레벨이 이거라면 하지마
	
	MapNames = GetWorld()->GetMapName();
	//MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);


	if (MapNames.Contains("lobby"))
	{
		return;
	}
	else
	{

		if (!bHasExecuted)
		{
			// 실행하려는 코드를 여기에 작성합니다.
			if (gm && gm->AllLevelArray.Num() > 0)
			{
				idnum = gm->AllLevelArray[0].Id;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AllLevelArray is empty or not initialized."));
			}

			// 코드를 실행한 후 bHasExecuted를 true로 설정합니다.
			bHasExecuted = true;
		}
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

		FName LevelName = "2_ViewLevel";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	
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
	//HttpActor->SendRequest(gi->AllMap);
	if (gm!= nullptr && !gm->AllLevelArray.IsEmpty())
	{
		SetWidgetText(idnum);
	}
	else if (Multigm != nullptr && !Multigm->AllLevelArray.IsEmpty())
	{
		SetWidgetMultiText(idnum);

	}
	
	UpdateButtonVisibility(0);
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

	FString MapName = GetWorld()->GetMapName();

	if (MapName.Contains("Single"))
	{
		FName LevelName = "PlanetariumSetup0";
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}
	//else if (MapName.Contains("Multi"))
	//{
	//	UWorld* World = GetWorld();
	//	if (World)
	//	{
	//		GetWorld()->ServerTravel("/Game/AccretionDisk/Levels/PlanetariumSetup0?Listen");
	//	}
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


void UMediaLobbyWidget::OnClickedbtn_BackDouble()
{
	SwitchCanvas(2);
}

void UMediaLobbyWidget::SetWidgetText(int id)
{
	FText IDText = FText::AsNumber(idnum);
	text_ID->SetText(IDText);

	FText TitleText = FText::FromString(gm->AllLevelArray[idnum-6].Title);
	text_Title->SetText(TitleText);

	FText SingerText = FText::FromString(gm->AllLevelArray[idnum-6].Singer);
	text_Singer->SetText(SingerText);

	FText ArtistText = FText::FromString(gm->AllLevelArray[idnum-6].MemberName);
	text_Artist->SetText(ArtistText);

	FText InfoText = FText::FromString(gm->AllLevelArray[idnum-6].Info);
	text_Info->SetText(InfoText);
}

void UMediaLobbyWidget::SetWidgetMultiText(int id)
{
	FText IDText = FText::AsNumber(idnum);
	text_ID->SetText(IDText);

	FText TitleText = FText::FromString(Multigm->AllLevelArray[idnum].Title);
	text_Title->SetText(TitleText);

	FText SingerText = FText::FromString(Multigm->AllLevelArray[idnum].Singer);
	text_Singer->SetText(SingerText);

	FText ArtistText = FText::FromString(Multigm->AllLevelArray[idnum].MemberName);
	text_Artist->SetText(ArtistText);

	FText InfoText = FText::FromString(Multigm->AllLevelArray[idnum].Info);
	text_Info->SetText(InfoText);
}

void UMediaLobbyWidget::SetID()
{
	gi->ReceiveLevelDataID(idnum);

	if (gm != nullptr)
	{
		gi->song = gm->AllLevelArray[idnum-6].Song;
		gi->singer=gm->AllLevelArray[idnum-6].Singer;

	}
	else if (Multigm != nullptr)
	{
		gi->song = Multigm->AllLevelArray[idnum].Song;
		gi->singer = Multigm->AllLevelArray[idnum].Singer;
	}
	// 레벨 트레블 해


	// 서버 트레블해
	//FName LevelName = "C_Ocean";

	//UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	UWorld* World = GetWorld();
	if (World)
	{
		GetWorld()->ServerTravel("/Game/ART/Sojin/MeteorMap?Listen");

	}
	
}

void UMediaLobbyWidget::SocialPlay(int LevelId)
{
	TArray<FAllLevelData> AllLevel = gm->AllLevelArray;
	AllLevel[LevelId].Id;
	UE_LOG(LogTemp,Warning,TEXT("SocialPlay Pressed"));
	if (!gi)
	{
		return;
	}

	//gi->song=LevelId;
	gi->ReceiveLevelDataID(LevelId);

	FString MapName = GetWorld()->GetMapName();
	if (MapName.Contains("Multi"))
	{
		UWorld* World = GetWorld();
		if (World)
		{
			GetWorld()->ServerTravel("/Game/DEV/Map/3_3CreateMap?Listen");
		}
	}
}

void UMediaLobbyWidget::UpdateButtonVisibility(int32 CanvasIndex)
{
	// WidgetSwitcher 참조를 가져옵니다.
	UWidgetSwitcher* CategorySwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("ws_CategorySwitcher")));

	// 버튼 위젯 참조를 가져옵니다.
	UButton* SingleButton = Cast<UButton>(GetWidgetFromName(TEXT("btn_Single")));
	UButton* SocialPlayButton = Cast<UButton>(GetWidgetFromName(TEXT("btn_SocialPlay")));

	if (CategorySwitcher && SingleButton && SocialPlayButton)
	{
		// 현재 캔버스 인덱스가 0이고, WidgetSwitcher의 인덱스가 0일 때
		if (CanvasIndex == 0 && CategorySwitcher->GetActiveWidgetIndex() == 0)
		{
			SingleButton->SetVisibility(ESlateVisibility::Visible);
			SocialPlayButton->SetVisibility(ESlateVisibility::Hidden);
		}
		// 현재 캔버스 인덱스가 0이고, WidgetSwitcher의 인덱스가 1일 때
		else if (CanvasIndex == 0 && CategorySwitcher->GetActiveWidgetIndex() == 1)
		{
			SingleButton->SetVisibility(ESlateVisibility::Hidden);
			SocialPlayButton->SetVisibility(ESlateVisibility::Visible);
		}
		
	}
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


