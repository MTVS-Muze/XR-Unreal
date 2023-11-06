// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJS_EnterRoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_EnterRoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=ViewMain)
	class UButton* btn_Enter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=MakingRoom)
	class UEditableText* edit_EnterRoomCode;
	
	UPROPERTY()
	class UOSY_GameInstance* gi;

	UFUNCTION()
	void OnEnterClicked();

};
