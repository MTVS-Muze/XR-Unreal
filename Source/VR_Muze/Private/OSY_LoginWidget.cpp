// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LoginWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_KakaoHttpRequestActor.h"
#include "WebBrowser.h"
#include "OSY_CreativeGameModeBase.h"

void UOSY_LoginWidget::NativeConstruct()
{
	btn_GoSignUp->OnClicked.AddDynamic(this,&UOSY_LoginWidget::GotoSignUpCanvas);
	btn_Login->OnClicked.AddDynamic(this, &UOSY_LoginWidget::Login);
	//btn_SignUp->OnClicked.AddDynamic(this, &UOSY_LoginWidget::SignUp);
	
	gm = Cast<AOSY_CreativeGameModeBase>(UGameplayStatics::GetGameMode(this));

	WebBrowser = Cast<UWebBrowser>(GetWidgetFromName(TEXT("WebBrowser")));
	if (WebBrowser)
	{
		WebBrowser->OnUrlChanged.AddDynamic(this, &UOSY_LoginWidget::HandleUrlChanged);
	}
}

void UOSY_LoginWidget::SwithLoginCanvas(int32 index)
{
	ws_LoginSwitcher->SetActiveWidgetIndex(index);
}

void UOSY_LoginWidget::GotoSignUpCanvas()
{
	SwithLoginCanvas(1);
}

void UOSY_LoginWidget::Login()
{
	
	WebBrowser->LoadURL(TEXT("http://192.168.0.5:8080/oauth2/authorize/kakao?redirect_uri=http://192.168.0.99:7777/oauth2/redirect"));

}

void UOSY_LoginWidget::LoginGet()
{
	if (KaKaoActor != nullptr)
	{
		KaKaoActor->SendRequest(url);
	}
}


void UOSY_LoginWidget::HandleUrlChanged(const FText& InText)
{
	FString Url = InText.ToString();

	// Extract the token from the URL
	Token2 = ExtractTokenFromUrl(Url);

	//UE_LOG(LogTemp, Warning, TEXT("Token :%s"), *Token);

	// If the token was successfully extracted, complete the login process
	if (!Token2.IsEmpty())
	{
		gm->Token=Token2;
		CompleteLogin(Token2);
	}
}

FString UOSY_LoginWidget::ExtractTokenFromUrl(const FString& Url)
{
	int32 questionMarkIndex;
	if (Url.FindChar('?', questionMarkIndex))
	{
		FString queryParams = Url.Mid(questionMarkIndex + 1);

		// Extract the token from the query parameters
		TArray<FString> params;
		queryParams.ParseIntoArray(params, TEXT("&"));
		for (const FString& param : params)
		{
			TArray<FString> keyValue;
			param.ParseIntoArray(keyValue, TEXT("="));
			if (keyValue.Num() == 2 && keyValue[0] == TEXT("token"))
			{
				return keyValue[1];  // Return the token
			}
		}
	}

	return TEXT("");  // If the token was not found

}

void UOSY_LoginWidget::CompleteLogin(const FString& Token)
{
	UE_LOG(LogTemp, Warning, TEXT("Login completed with token: %s"), *Token);

	
}

