// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ModeSelect)
	class UWidgetSwitcher* ws_UISwitch;

public:
	//ModeSelect 캔버스

	//미디어모드 가기
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ModeSelect)
	class UButton* btn_Media;

	//크리에이트모드 가기
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ModeSelect)
	class UButton* btn_Creative;

public:
	//BoxList 캔버스
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=BoxList)
	class UScrollBox* sb_BoxList;

	//뒤로가기
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=BoxList)
	class UButton* btn_BackModeSelect;
	
	//생성하기 버튼
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=BoxList)
	class UButton* btn_CreateBox;

	UPROPERTY(EditAnywhere, Category = BoxList)
	TSubclassOf<class UCreatedBoxInfo> BoxInfoWidget;

public:
	//CreateSettings 캔버스
	//최종 박스 생성
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UButton* btn_Create;

	//박스리스트 돌아가기
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UButton* btn_BackBoxList;

	//박스이름 EditableTextBlock
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UEditableText* edit_BoxName;

	//음악선택 콤보박스string
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UComboBoxString* cbs_MusicList;


//함수 리스트
public:
	void SwitchCanvas(int32 index);

/////////////////////////////////////////
//UI인덱스 0
/////////////////////////////////////////
	UFUNCTION()
	void OnClickedButtonMedia();

	UFUNCTION()
	void OnClickedButtonCreativeMode();

/////////////////////////////////////////
//UI인덱스 1
/////////////////////////////////////////

//박스리스트 추가 함수

	UFUNCTION()
	void OnClickedButtonBackModeSelect();

	UFUNCTION()
	void OnClickedButtonCreateBox();

/////////////////////////////////////////
//UI인덱스 2
/////////////////////////////////////////
	UFUNCTION()
	void OnClickedButtonCreateEnd();

	UFUNCTION()
	void OnClickedButtonBackBoxList();

};
