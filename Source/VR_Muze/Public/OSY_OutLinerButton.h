// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "OSY_OutLinerButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, AActor*, Actor);

UCLASS()
class VR_MUZE_API UOSY_OutLinerButton : public UButton
{
	GENERATED_BODY()

public:
    UPROPERTY()
    AActor* LinkedActor;

    // 클릭된 버튼이 가리키는 액터를 설정하고 반환하는 함수를 추가합니다.
    UFUNCTION()
    void SetTargetActor(AActor* NewTargetActor);

    UFUNCTION()
    AActor* GetTargetActor();

     UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnButtonClicked OnButtonClickedDelegate;

private:
    AActor* TargetActor;

protected:
    virtual void SynchronizeProperties() override;

    UFUNCTION()
    void OnButtonClicked();

	
};
