// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Plugins/Runtime/WebBrowserWidget/Source/WebBrowserWidget/Public/WebBrowser.h"
#include "OSY_LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_LoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UWidgetSwitcher* ws_LoginSwitcher;

	UFUNCTION()
	void SwithLoginCanvas(int32 index);

public:
#pragma region SeverData;
	//UPROPERTY()
	//FString url ="http://192.168.0.232:8080/map/test/1";

	UPROPERTY()
	FString url ="http://192.168.0.6:8080/give/token";
#pragma endregion
#pragma region LoginCanvas

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UEditableText* edit_LoginID;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UEditableText* edit_LoginPW;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UButton* btn_GoSignUp;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UButton* btn_Login;
	


	UFUNCTION()
	void GotoSignUpCanvas();
	UFUNCTION()
	void Login();

	UFUNCTION()
	void LoginGet();

	UPROPERTY()
	class AOSY_KakaoHttpRequestActor* KaKaoActor;


#pragma endregion

#pragma region ApplyCanvas


	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UEditableText* edit_SignUpID;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UEditableText* edit_SignUpPW;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UButton* btn_SignUp;

	UFUNCTION()
	void HandleUrlChanged(const FText& InText);

	  UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	   UWebBrowser* WebBrowser;

	   FString ExtractTokenFromUrl(const FString& Url);

	   void CompleteLogin(const FString& Token);

	   FString Token2;
	  UPROPERTY(BlueprintReadOnly)
	  class AOSY_CreativeGameModeBase* gm;
#pragma endregion


};
