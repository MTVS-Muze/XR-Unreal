// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreatedBoxInfo.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UCreatedBoxInfo : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Info)
	class UImage* img_Thumnail;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Info)
	class UTextBlock* text_BoxName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Info)
	class UTextBlock* text_MadeDate;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Info)
	class UButton* btn_EnterLevel;

public:
	UFUNCTION()
	void EnterLevel();
};
