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

	// ���� A��� �̸��� �����̸� ��ư�� �Լ��� GotoCreativeLevel����
	if(LevelName2 == "ViewLevel")
	{
		btn_SwitchCreative->OnClicked.Clear(); // ������ ������ Ŭ�� �̺�Ʈ�� �����մϴ�.
		btn_SwitchCreative->OnClicked.AddDynamic(this, &UMainWidget::GotoCreativeLevel); // ���ο� Ŭ�� �̺�Ʈ�� �߰��մϴ�.
	}
	// �׷��� �ʰ� B��� �̸��̸� ��ư�� �Լ��� GotoCreativeLeve2����
	else if(LevelName2 == "CreativeLevel")
	{
		btn_SwitchCreative->OnClicked.Clear(); // ������ ������ Ŭ�� �̺�Ʈ�� �����մϴ�.
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
	// ���忡 ��ġ�� ���� ������ ã��
	for (TActorIterator<ALevelSequenceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		LevelSequenceActor = *ActorItr;
		break;
	}

	// ���� �������� ����� ã�������� Ȯ��
	if (LevelSequenceActor)
	{
		// ���� �������� �÷��̾� ��������
		UMovieSceneSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();


		if (LevelSequenceActor)
		{
			//UMovieSceneSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();

			// ���� �������� OnFinished �̺�Ʈ�� ���ε�
			Player->OnFinished.AddDynamic(this, &UMainWidget::OnStop);

			// ���� �������� ��� ���� ��ġ�� 1�ʷ� ����
			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime(1 * 30); // assuming 30fps
			Player->SetPlaybackPosition(Params);

			// ���� ������ ���
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
	// ���Լ��� ������� 3�ʰ� �귶�ٸ� ������ �ٲٰ� �ʹ�
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

		// ��� ��ġ�� 1�ʷ� �ǵ���
		FMovieSceneSequencePlaybackParams Params;
		Params.Frame = FFrameTime(1 * 30); // assuming 30fps
		Player->SetPlaybackPosition(Params);

		// �ٽ� ���
		Player->Play();
	}
}
