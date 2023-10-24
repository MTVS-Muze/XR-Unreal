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
	//Ã³À½ À§Á¬
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ModeSelect)
	class UWidgetSwitcher* ws_SwitchSofa;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = ModeSelect)
	class UEditableText* edit_roomName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = ModeSelect)
	class USlider* slider_playerCount;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = ModeSelect)
	class UButton* btn_Next;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = ModeSelect)
	class UButton* btn_Back;

	class UOSY_GameInstance* gi;
public:
	UFUNCTION()
	void InitializeComboBox();

	//UFUNCTION()
	//void OnComboBoxSelectionChanged(FString SelectedNum, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnClickCreateRoom();

};
