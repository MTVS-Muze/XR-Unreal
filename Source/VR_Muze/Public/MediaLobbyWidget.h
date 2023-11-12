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
	class UButton* btn_BackMain;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_Single;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_Multi;

	UPROPERTY()
	class AKJS_Box* MediaBox;
////////////////////////////////////////////////
//Canvas Original
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Main)
	class UWidgetSwitcher* ws_CategorySwitcher;

	UFUNCTION()
	void SwitchCanvasCategory(int32 index);

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_UpOriginal;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_DownOriginal;
	
//Original 노래 리스트
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_SuperShy;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song2;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song3;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song4;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song5;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song6;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song7;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song8;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song9;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	TArray<UButton*> List;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_LeftOriginal;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_RightOriginal;

	UPROPERTY()
	FString RoomCode;


public:
	//Canvas_Origianl 바인딩 함수
	UFUNCTION()
	void BackSelectMode();

	UFUNCTION()
	void JoinRoom();

	UFUNCTION()
	void CreateRoom();

	UFUNCTION()
	void OnClickedbtn_Left();

	UFUNCTION()
	void OnClickedbtn_Right();

	UFUNCTION()
	void OnClickedbtn_UpOriginal();

	UFUNCTION()
	void OnClickedbtn_DownOriginal();

public:
//Canvas Social
UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_UpSocial;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_DownSocial;
	
//Original 노래 리스트
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_SuperShySocial;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song2Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song3Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song4Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song5Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song6Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song7Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song8Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song9Social;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_Song10Social;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	TArray<UButton*> ListSocial;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_LeftSocial;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Original)
	class UButton* btn_RightSocial;

public:
	//Canvas_Social 바인딩 함수
	UFUNCTION()
	void OnClickedbtn_UpSocial();

	UFUNCTION()
	void OnClickedbtn_DownSocial();


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
	void OnCheckedSignleSit1(bool bIsChcecked);

	UFUNCTION()
	void OnCheckedSingleSit2(bool bIsChcecked);


public:
	//Double 요소
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=DoublePanel)
	class UButton* btn_CreateDouble;

		UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=DoublePanel)
	class UCheckBox* Check_DoubleSit1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=DoublePanel)
	class UCheckBox* Check_DoubleSit2;

public:
	//Double 함수
	UFUNCTION()
	void CreateDoubleRoom();

	UFUNCTION()
	void OnCheckedDoubleSit1(bool bIsChcecked);

	UFUNCTION()
	void OnCheckedDoubleSit2(bool bIsChcecked);

private:
	UPROPERTY()
	class AMyCharacter* player;




};
