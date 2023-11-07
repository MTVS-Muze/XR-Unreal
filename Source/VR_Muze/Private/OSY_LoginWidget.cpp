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


	// ���̵�� ����� ������ ������
	// ���� ������ ���̵� ����̶�� ������ �ٲ۴�
	// �׷��� ������ �ƹ� �ϵ� �Ͼ�� �ʴ´� or �߸��� ���̵� ����̶�� �˷��ִ� UI�� ����.
}

void UOSY_LoginWidget::SignUp()
{
	// ���̵�� ����� ������ ������
	// ȸ�������� �Ϸ�Ǹ� �Ϸ�Ǿ��ٴ� UI�� ����
	// UI�� �ִ� Ȯ�� ��ư�� ������ ĵ������ �ٲ۴�.

}
