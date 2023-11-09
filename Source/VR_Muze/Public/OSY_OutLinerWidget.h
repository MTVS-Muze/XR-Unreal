// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "OSY_OutLinerWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_OutLinerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UScrollBox* sb_OutLiner;

    // ���忡 �ִ� ��� ���͸� �������� �Լ�
    TArray<AActor*> GetAllActorsInWorld();

    // ���� ������ UI�� ǥ���ϴ� �Լ�
    UFUNCTION()
    void DisplayActorInfo();

    //UFUNCTION()
    //void OnButtonClicked();

   

    UPROPERTY(EditAnywhere,Category= MySettings)
    FString ActorName;
    UPROPERTY(EditAnywhere,Category= MySettings)
    FString ActorType;
    UPROPERTY(EditAnywhere,Category= MySettings)
    class UOSY_OutLinerButton* Button;

    UPROPERTY(EditAnywhere,Category= MySettings)
    TMap<UButton*, AActor*> ButtonToActorMap;



};
	

