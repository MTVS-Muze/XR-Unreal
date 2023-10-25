// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChoiceSofaPeopleNumWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UChoiceSofaPeopleNumWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	//À§Á¬1
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UScrollBox* sb_RoomList;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_BackMain;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_Join;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_CreateRoom;

	UFUNCTION()
	void SwitchCanvas(int32 index);

public:
	//À§Á¬2
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MakingRoom)
	class UWidgetSwitcher* ws_SwitchSofa;

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

	class UOSY_GameInstance* gi;
public:
	UFUNCTION()
	void OnSliderMoved(float value);

	UFUNCTION()
	void OnClickNextButton(int32 index);



};
