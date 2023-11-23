// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LoginWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_KakaoHttpRequestActor.h"
#include "WebBrowser.h"
#include "OSY_GameInstance.h"
#include "OSY_LoginGameMode.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/MovieScene/Public/MovieSceneSequencePlayer.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "OSY_HttpRequestActor.h"
#include "OSY_GameInstance.h"

void UOSY_LoginWidget::NativeConstruct()
{


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
			Player->OnFinished.AddDynamic(this, &UOSY_LoginWidget::OnStop);

			// 레벨 시퀀스의 재생 시작 위치를 1초로 설정
			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime(1 * 30); // assuming 30fps
			Player->SetPlaybackPosition(Params);

			// 레벨 시퀀스 재생
			Player->Play();
		}
	}


	btn_Login->OnClicked.AddDynamic(this, &UOSY_LoginWidget::GotoLoginCanvas);
	btn_Start->OnClicked.AddDynamic(this, &UOSY_LoginWidget::GotoLobbyMap);
	
	loginGM = Cast<AOSY_LoginGameMode>(UGameplayStatics::GetGameMode(this));
	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

 	WebBrowser = Cast<UWebBrowser>(GetWidgetFromName(TEXT("WebBrowser")));
 	if (WebBrowser)
 	{
 		WebBrowser->OnUrlChanged.AddDynamic(this, &UOSY_LoginWidget::HandleUrlChanged);
 	}

}


#pragma region SwitchCanvas
void UOSY_LoginWidget::SwithLoginCanvas(int32 index)
{
	ws_LoginSwitcher->SetActiveWidgetIndex(index);
}

void UOSY_LoginWidget::GotoLoginCanvas()
{
	SwithLoginCanvas(1);

}

void UOSY_LoginWidget::GotoStartCanvas()
{



	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOSY_LoginWidget::GetCustom, 1.0f, false);


	//GetCustom();
	
	
}

void UOSY_LoginWidget::GotoLobbyMap()
{
	FName LevelName = "1_2CH_MAP";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

#pragma endregion 


void UOSY_LoginWidget::SwithchCanvas()
{

	SwithLoginCanvas(2);
}

void UOSY_LoginWidget::HandleUrlChanged(const FText& InText)
{
	FString Url = InText.ToString();

	Token2 = ExtractTokenFromUrl(Url);
	BearerToken = "Bearer " + Token2;

	if (!Token2.IsEmpty())
	{
		UOSY_GameInstance* MyGameInstance = Cast<UOSY_GameInstance>(GetWorld()->GetGameInstance());
		if (MyGameInstance != nullptr)
		{


			MyGameInstance->Token= BearerToken;
			if (!MyGameInstance->Token.IsEmpty())
			{
				UE_LOG(LogTemp,Warning,TEXT("Token : %s"),*MyGameInstance->Token);
				GotoStartCanvas();
			}
		}
	}
}

FString UOSY_LoginWidget::ExtractTokenFromUrl(const FString& Url)
{
	int32 questionMarkIndex;
	if (Url.FindChar('?', questionMarkIndex))
	{
		FString queryParams = Url.Mid(questionMarkIndex + 1);

		TArray<FString> params;
		queryParams.ParseIntoArray(params, TEXT("&"));
		for (const FString& param : params)
		{
			TArray<FString> keyValue;
			param.ParseIntoArray(keyValue, TEXT("="));
			if (keyValue.Num() == 2 && keyValue[0] == TEXT("token"))
			{
				return keyValue[1];
			}
		}
	}

	return TEXT(""); 

}


void UOSY_LoginWidget::OnStop()
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

void UOSY_LoginWidget::GetCustom()
{
	HttpActor->SendRequest(gi->CustomURL);

	

	SwithchCanvas();
}

void UOSY_LoginWidget::BackToMain()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}
