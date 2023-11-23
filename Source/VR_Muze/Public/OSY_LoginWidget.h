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
	

	UPROPERTY()
	FString url ="http://192.168.0.189:8080/give/token";
#pragma endregion



#pragma region LoginCanvas

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UButton* btn_Login;

	UFUNCTION()
	void GotoLoginCanvas();

#pragma endregion

#pragma region LoginWeb
	UFUNCTION()
	void GotoStartCanvas();
#pragma endregion

#pragma region StartCanvas


	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Login)
	class UButton* btn_Start;


#pragma endregion

#pragma region LoginCanvas

	UFUNCTION()
	void GotoLobbyMap();
	
	

	UFUNCTION()
	void BackToMain();

	UPROPERTY()
	class AOSY_KakaoHttpRequestActor* KaKaoActor;


	// Info
	
	UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;

	UPROPERTY()
	class UOSY_GameInstance* gi;


	



	
#pragma endregion
	UFUNCTION()
	void SwithchCanvas();

#pragma region GetToken

	UFUNCTION()
	void HandleUrlChanged(const FText& InText);

	  UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	   UWebBrowser* WebBrowser;

	   FString ExtractTokenFromUrl(const FString& Url);


	   FString Token2;
#pragma endregion

UPROPERTY()
	class ALevelSequenceActor* LevelSequenceActor= nullptr; // 멤버 변수로 선언

	UFUNCTION()
	void OnStop();

	UFUNCTION()
	void GetCustom();


	UPROPERTY()
	FString BearerToken;



};
