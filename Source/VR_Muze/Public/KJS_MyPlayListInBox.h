// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJS_MyPlayListInBox.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_MyPlayListInBox : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_ListBack;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Play;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Stop;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_ListFront;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=PlayList)
	class UScrollBox* sb_PlayList;

public:
	UFUNCTION()
	void PlayBack();

	UFUNCTION()
	void PlayMedia();

	UFUNCTION()
	void StopMedia();

	UFUNCTION()
	void PlayFrontMedia();
	
};
