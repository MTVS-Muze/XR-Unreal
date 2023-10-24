// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJS_ViewModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_ViewModeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ModeSelect)
	class UWidgetSwitcher* ws_UISwitch;

	UFUNCTION()
	void SwitchIndex(int32 index);
	
};
