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



void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

	btn_MediaEnter->OnClicked.AddDynamic(this, &UMainWidget::mediaPlay);

	LevelName2 = UGameplayStatics::GetCurrentLevelName(this);

	// 만약 A라는 이름의 레벨이면 버튼에 함수를 GotoCreativeLevel로해
	if(LevelName2 == "ViewLevel")
	{
		btn_SwitchCreative->OnClicked.Clear(); // 기존에 설정된 클릭 이벤트를 제거합니다.
		btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::GotoCreativeLevel); // 새로운 클릭 이벤트를 추가합니다.
	}
	// 그렇지 않고 B라는 이름이면 버튼에 함수를 GotoCreativeLeve2로해
	else if(LevelName2 == "CreativeLevel")
	{
		btn_SwitchCreative->OnClicked.Clear(); // 기존에 설정된 클릭 이벤트를 제거합니다.
		btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::createPlay);
	}


	//JSCode
	/*
	btn_MediaEnter->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonMedia);
	btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonSwitchCreative);
	*/
	//btn_CreativeEnter->OnClicked.AddDynamic(this, &UMainWidget::OnClickedButtonCreativeMode);
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
		FName LevelName = "Yellow_Single";

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

	FName LevelName = "OSY_TMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UMainWidget::OnClickedButtonCreateEnd()
{
	//SwitchCanvas(2);

	FName LevelName = "3_CreativeMap";

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
	FName LevelName = "CreativeLevel";

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
