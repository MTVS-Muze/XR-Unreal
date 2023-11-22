// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "OSY_MainWidgetButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainButtonClicked, int, ID);

UCLASS()
class VR_MUZE_API UOSY_MainWidgetButton : public UButton
{
	GENERATED_BODY()

public:

	int LevelDataID;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FMainButtonClicked OnButtonClickedDelegate;

	UFUNCTION()
	void SetId(int ID);

	UFUNCTION()
	int GetID();

	virtual void SynchronizeProperties() override;

	UFUNCTION()
    void OnButtonClicked();

	
};
