// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCustomizeWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UCharacterCustomizeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Main)
	class UWidgetSwitcher* ws_CharacterCustomize;

	UFUNCTION()
	void SwitchCanvas(int32 index);

	UPROPERTY()
	class AMyCharacter* player;
public:
////////////////////////////////////////////
//Canvas_Select
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Select)
	class UButton* btn_IntoBox;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Select)
	class UButton* btn_IntoCustomize;	


public:
	UFUNCTION()
	void OnClickedbtn_IntoBox();

	UFUNCTION()
	void OnClickedbtn_IntoCustomize();


public:
///////////////////////////////////
//Canvas Customize
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Customize)
	class UButton* btn_Save;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Customize)
	class UButton* btn_Back;

	UFUNCTION()
	void OnClickedbtn_CustomizeSave();

	UFUNCTION()
	void OnClickedbtn_BackSelect();

//Color Panel
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Black;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_White;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_SkyBlue;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Pink;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Yellow;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Green;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_DeepYellow;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Violet;	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Coral;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ColorBtn)
	class UButton* btn_Navy;
	
public:
	UFUNCTION()
	void SwitchColorBlack();

	UFUNCTION()
	void SwitchColorWhite();

	UFUNCTION()
	void SwitchColorSkyBlue();

	UFUNCTION()
	void SwitchColorPink();

	UFUNCTION()
	void SwitchColorYellow();

	UFUNCTION()
	void SwitchColorGreen();

	UFUNCTION()
	void SwitchColorDeepYellow();

	UFUNCTION()
	void SwitchColorViolet();

	UFUNCTION()
	void SwitchColorCoral();

	UFUNCTION()
	void SwitchColorNavy();
};
