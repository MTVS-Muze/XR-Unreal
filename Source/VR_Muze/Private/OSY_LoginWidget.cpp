// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LoginWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_KakaoHttpRequestActor.h"
#include "WebBrowser.h"
#include "OSY_GameInstance.h"
#include "OSY_LoginGameMode.h"

void UOSY_LoginWidget::NativeConstruct()
{
	btn_Start->OnClicked.AddDynamic(this, &UOSY_LoginWidget::GotoLoginCanvas);

	
	
	loginGM = Cast<AOSY_LoginGameMode>(UGameplayStatics::GetGameMode(this));

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

void UOSY_LoginWidget::GotoLobbyMap()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

#pragma endregion 

void UOSY_LoginWidget::Login()
{
	
	WebBrowser->LoadURL(TEXT("http://192.168.0.5:8080/oauth2/authorize/kakao?redirect_uri=http://192.168.0.99:7777/oauth2/redirect"));

}


void UOSY_LoginWidget::HandleUrlChanged(const FText& InText)
{
	FString Url = InText.ToString();

	Token2 = ExtractTokenFromUrl(Url);

	if (!Token2.IsEmpty())
	{
		UOSY_GameInstance* MyGameInstance = Cast<UOSY_GameInstance>(GetWorld()->GetGameInstance());
		if (MyGameInstance != nullptr)
		{
			MyGameInstance->Token=Token2;
			if (!MyGameInstance->Token.IsEmpty())
			{
				CompleteLogin(Token2);
				GotoLobbyMap();
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

void UOSY_LoginWidget::CompleteLogin(const FString& Token)
{
	UE_LOG(LogTemp, Warning, TEXT("Login completed with token: %s"), *Token);

	
}

void UOSY_LoginWidget::BackToMain()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}
