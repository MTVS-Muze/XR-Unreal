// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJS_RuntimeActiveEffectWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_RuntimeActiveEffectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
