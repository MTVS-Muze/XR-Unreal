// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJS_TypeInviteNumWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_TypeInviteNumWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category=Base)
	class UTextBlock* text_InviteCode;

	UFUNCTION()
	void CreateInviteCode(const FString& InviteCode);

	UPROPERTY()
	class UOSY_GameInstance* gi;

};
