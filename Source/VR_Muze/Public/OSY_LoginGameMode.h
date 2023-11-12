// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OSY_LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AOSY_LoginGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOSY_LoginGameMode();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_LoginWidget>LoginWidget;
	class UOSY_LoginWidget* LoginUI;

private:
	
};
