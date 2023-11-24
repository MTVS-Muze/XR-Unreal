// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OSY_MyInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_MyInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Settings)
	class UTextBlock* tb_Name;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Settings)
	class UTextBlock* tb_email;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= Settings)
	class UImage* img_profile;


	UPROPERTY()
	class UOSY_GameInstance* gi;

	UPROPERTY()
	class AKJS_CustomizeGameModeBase* KCgm;

	UFUNCTION()
	void SetText();

	UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;
	
};
