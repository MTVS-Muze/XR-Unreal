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

	UPROPERTY(BlueprintReadOnly)
	class AOSY_LoginGameMode* loginGM;

public:
#pragma region SeverData;
	//UPROPERTY()
	//FString url ="http://192.168.0.232:8080/map/test/1";

	UPROPERTY()
	FString url ="http://192.168.0.189:8080/give/token";
#pragma endregion

#pragma region StartCanvas


	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UButton* btn_Start;

	UFUNCTION()
	void GotoLoginCanvas();

#pragma endregion

#pragma region LoginCanvas

	UFUNCTION()
	void GotoLobbyMap();
	
	UFUNCTION()
	void Login();

	UFUNCTION()
	void BackToMain();

	UPROPERTY()
	class AOSY_KakaoHttpRequestActor* KaKaoActor;


	



	
#pragma endregion

#pragma region GetToken

	UFUNCTION()
	void HandleUrlChanged(const FText& InText);

	  UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	   UWebBrowser* WebBrowser;

	   FString ExtractTokenFromUrl(const FString& Url);

	   void CompleteLogin(const FString& Token);

	   FString Token2;
#pragma endregion

UPROPERTY()
	class ALevelSequenceActor* LevelSequenceActor= nullptr; // 멤버 변수로 선언

	UFUNCTION()
	void OnStop();



};
