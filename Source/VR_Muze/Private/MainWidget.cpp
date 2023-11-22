// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_GameInstance.h"
#include "Components/CanvasPanel.h" 
#include "HeadMountedDisplayFunctionLibrary.h"
#include "IXRTrackingSystem.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/MovieScene/Public/MovieSceneSequencePlaybackSettings.h"
#include "Engine/World.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "EngineUtils.h"
#include "LevelSequenceActor.h" 
#include "Runtime/Core/Public/Misc/Timespan.h"
#include "Runtime/MovieScene/Public/MovieSceneSequencePlayer.h"
#include "ModeSelectGameModeBase.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "OSY_HttpRequestActor.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "OSY_MainWidgetButton.h"



void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MSgm=GetWorld()->GetAuthGameMode<AModeSelectGameModeBase>();
	gi = Cast<UOSY_GameInstance>(GetGameInstance());
	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));
	
	LevelName2 = UGameplayStatics::GetCurrentLevelName(this);


	// 버튼미디어 엔터
	// 만약 레벨이름이 2뭐시기라면
	// 이전이벤트 날리고 다시 재생해
	// 그렇지 않다면
	// 이전이벤트 날리고 뷰레벨로가
	if (LevelName2 == "2_ViewLevel")
	{
		btn_MediaEnter->OnClicked.Clear(); // 기존에 설정된 클릭 이벤트를 제거합니다.
		btn_MediaEnter->OnClicked.AddDynamic(this, &UMainWidget::mediaPlay); // 새로운 클릭 이벤트를 추가합니다.
		btn_SwitchCreative->OnClicked.Clear(); // 기존에 설정된 클릭 이벤트를 제거합니다.
		btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::GotoCreativeLevel); // 새로운 클릭 이벤트를 추가합니다.
	}
	// 그렇지 않고 B라는 이름이면 버튼에 함수를 GotoCreativeLeve2로해
	else if (LevelName2 == "3_CreativeLevel")
	{
		btn_MediaEnter->OnClicked.Clear(); // 기존에 설정된 클릭 이벤트를 제거합니다.
		btn_MediaEnter->OnClicked.AddDynamic(this, &UMainWidget::GotoViewLevel);
		btn_SwitchCreative->OnClicked.Clear(); // 기존에 설정된 클릭 이벤트를 제거합니다.
		btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::createPlay);
	}


	
	btn_BackModeSelect->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonBackModeSelect);
	btn_CreateBox->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreateBox);
	btn_Create->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreateEnd);
	btn_BackBoxList->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonBackBoxList);
	btn_HiddenErrorUI->OnClicked.AddDynamic(this, &UMainWidget::OnClickedHiddenErrorUI);



	if (ErrorUI)
	{
		ErrorUI->SetVisibility(ESlateVisibility::Hidden);
	}


//-----------------------------
	// 월드에 배치된 레벨 시퀀스 찾기
	for (TActorIterator<ALevelSequenceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		LevelSequenceActor = *ActorItr;
		break;
	}

	// 레벨 시퀀스가 제대로 찾아졌는지 확인
	if (LevelSequenceActor)
	{
		// 레벨 시퀀스의 플레이어 가져오기
		UMovieSceneSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();


		if (LevelSequenceActor)
		{
			//UMovieSceneSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();

			// 레벨 시퀀스의 OnFinished 이벤트에 바인딩
			Player->OnFinished.AddDynamic(this, &UMainWidget::OnStop);

			// 레벨 시퀀스의 재생 시작 위치를 1초로 설정
			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime(1 * 30); // assuming 30fps
			Player->SetPlaybackPosition(Params);

			// 레벨 시퀀스 재생
			Player->Play();
		}
	}
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

}

void UMainWidget::SwitchCanvas(int32 index)
{
	ws_UISwitch->SetActiveWidgetIndex(index);
}

void UMainWidget::OnClickedButtonMedia()
{
	
	if (GEngine->XRSystem.IsValid())
	{
		FName LevelName = "Box_indoor_Single";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}

	else
	{
		ErrorUI->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void UMainWidget::OnClickedButtonSwitchCreative()
{

	SwitchCanvas(1);
}

void UMainWidget::OnClickedButtonCreativeMode()
{
	DisplayLevelInfo();
	SwitchCanvas(2);

}

void UMainWidget::OnClickedHiddenErrorUI()
{
	if (ErrorUI)
	{
		ErrorUI->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UMainWidget::OnClickedButtonBackModeSelect()
{
	SwitchCanvas(2);
}

void UMainWidget::OnClickedButtonCreateBox()
{
	//SwitchCanvas(2);

	FName LevelName = "3_2CreateInfo";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UMainWidget::OnClickedButtonCreateEnd()
{
	//SwitchCanvas(2);

	FName LevelName = "3_2CreateInfo";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UMainWidget::OnClickedButtonBackBoxList()
{
	SwitchCanvas(2);
}

void UMainWidget::mediaPlay()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainWidget::OnClickedButtonMedia, 3.0f, false);

}

void UMainWidget::createPlay()
{
	// 이함수가 실행된지 3초가 흘렀다면 래밸을 바꾸고 싶다
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainWidget::OnClickedButtonCreativeMode, 3.0f, false);
}

void UMainWidget::GotoCreativeLevel()
{
	FName LevelName = "3_CreativeLevel";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

}

void UMainWidget::GotoViewLevel()
{
	FName LevelName = "2_ViewLevel";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);

}

void UMainWidget::OnStop()
{
	if (LevelSequenceActor)
	{
		UMovieSceneSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();

		// 재생 위치를 1초로 되돌림
		FMovieSceneSequencePlaybackParams Params;
		Params.Frame = FFrameTime(1 * 30); // assuming 30fps
		Player->SetPlaybackPosition(Params);

		// 다시 재생
		Player->Play();
	}
}

void UMainWidget::DisplayLevelInfo()
{
	TArray<FAllLevelData> AllLevel = MSgm->AllLevelArray;

	if (sb_BoxList)
	{
		vb_Level->ClearChildren();
	}

	for (int i = 0; i < AllLevel.Num(); ++i)
	{
		UHorizontalBox* HorizontalBoxWidget = NewObject<UHorizontalBox>(this);
		if (HorizontalBoxWidget)
		{
			// 버튼 위젯 생성
			ButtonWidget = NewObject<UOSY_MainWidgetButton>(this);
			if (ButtonWidget)
			{	
				ButtonWidget->SetId(i);
				// 버튼을 호리즌탈 박스에 추가
				ButtonWidget->LevelDataID = AllLevel[i].Id;
				HorizontalBoxWidget->AddChild(ButtonWidget);
				//ButtonWidget->OnClicked.AddDynamic(this, &UMainWidget::OnButtonClicked);
			}

			// 텍스트 위젯 생성
			UTextBlock* TextWidget = NewObject<UTextBlock>(this);
			if (TextWidget)
			{
				// 위젯에 텍스트 설정
				FText Text = FText::FromString(AllLevel[i].Title);
				TextWidget->SetText(Text);
				// 텍스트 위젯을 호리즌탈 박스에 추가
				HorizontalBoxWidget->AddChild(TextWidget);
			}

			// 호리즌탈 박스를 버티컬 박스에 추가
			vb_Level->AddChild(HorizontalBoxWidget);

			ButtonWidget->OnButtonClickedDelegate.AddDynamic(this, &UMainWidget::OnButtonClicked);
		}
	}
}

void UMainWidget::OnButtonClicked(int LevelId)
{
	if (!gi)
	{
		return;
	}

	gi->ReceiveLevelDataID(LevelId);


	FName LevelName = "3_3CreateMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	
}

