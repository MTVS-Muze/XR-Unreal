// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UMediaLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	//통합

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Main)
	class UWidgetSwitcher* ws_Switcher;

	UFUNCTION()
	void SwitchCanvas(int32 index);

public:
	//ViewMain
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UScrollBox* sb_RoomList;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_BackMain;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_Join;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_CreateRoom;

public:
	//ViewMain 바인딩 함수
	UFUNCTION()
	void BackSelectMode();

	UFUNCTION()
	void JoinRoom();

	UFUNCTION()
	void CreateRoom();


public:
	//MakingRoom
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=MakingRoom)
	class UEditableText* edit_roomName;				

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=MakingRoom)
	class USlider* slider_playerCount;				
													
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=MakingRoom)
	class UTextBlock* text_sliderCount;				
													
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=MakingRoom)
	class UButton* btn_Next;						
													
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=MakingRoom)
	class UButton* btn_Back;

	UPROPERTY()
	class UOSY_GameInstance* gi;

public:
	//MakingRoom 바인딩 함수
	UFUNCTION()
	void OnSliderMoved(float value);

	UFUNCTION()
	void OnClickNextButton();

	UFUNCTION()
	void OnClickBackButton();
	
public:
	//Single 요소
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=SinglePanel)
	class UCheckBox* Check_SingleSit1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=SinglePanel)
	class UCheckBox* Check_SingleSit2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=SinglePanel)
	class UImage* img_SingleSit1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=SinglePanel)
	class UImage* img_SingleSit2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=SinglePanel)
	class UButton* btn_BackSingle;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=SinglePanel)
	class UButton* btn_CreateSingle;

	UPROPERTY(EditAnywhere)
	class AKJS_BoxSofa* BoxSofa;

public:
	//Single 함수
	UFUNCTION()
	void BackMakingRoom();

	UFUNCTION()
	void CreateSingleRoom();

	UFUNCTION()
	void OnCheckedSit1(bool bIsChcecked);

	UFUNCTION()
	void OnCheckedSit2(bool bIsChcecked);


};
