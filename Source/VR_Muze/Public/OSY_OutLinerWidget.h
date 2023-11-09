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

    // 월드에 있는 모든 액터를 가져오는 함수
    TArray<AActor*> GetAllActorsInWorld();

    // 액터 정보를 UI에 표시하는 함수
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
	

