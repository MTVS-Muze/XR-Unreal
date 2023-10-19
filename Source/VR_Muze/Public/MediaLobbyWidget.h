// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UMediaLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Back;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Join;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_CreateRoom;
	

public:
	UFUNCTION()
	void BackSelectMode();

	UFUNCTION()
	void JoinRoom();

	UFUNCTION()
	void CreateRoom();
};
