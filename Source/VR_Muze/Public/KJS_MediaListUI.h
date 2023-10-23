// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJS_MediaListUI.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_MediaListUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	//재생버튼
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ModeSelect)
	class UButton* btn_Play;

public:
	UFUNCTION()
	void TransferPlayMediaLevel();
};
