// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_LoginWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UOSY_LoginWidget::NativeConstruct()
{
	btn_GoSignUp->OnClicked.AddDynamic(this,&UOSY_LoginWidget::GotoSignUpCanvas);
	btn_Login->OnClicked.AddDynamic(this, &UOSY_LoginWidget::Login);
	btn_SignUp->OnClicked.AddDynamic(this, &UOSY_LoginWidget::SignUp);
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
	
	FPlatformProcess::LaunchURL(TEXT("https://kauth.kakao.com/oauth/authorize?client_id=36ce23c011d844b5cc982ada079f8034&redirect_uri=http://localhost:8080/oauth2/callback/kakao&response_type=code"),NULL,NULL);


	// 아이디랑 비번을 서버에 보낸다
	// 만약 유요한 아이디 비번이라면 레벨을 바꾼다
	// 그렇지 않으면 아무 일도 일어나지 않는다 or 잘못된 아이디 비번이라고 알려주는 UI를 띄운다.
}

void UOSY_LoginWidget::SignUp()
{
	// 아이디랑 비번을 서버에 보낸다
	// 회원가입이 완료되면 완료되었다는 UI를 띄우고
	// UI에 있는 확인 버튼을 누르면 캔버스를 바꾼다.

}
