// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "OSY_OutLinerButton.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_OutLinerButton : public UButton
{
	GENERATED_BODY()

public:
    UPROPERTY()
    AActor* LinkedActor;

	public:
    // 클릭된 버튼이 가리키는 액터를 설정하고 반환하는 함수를 추가합니다.
    UFUNCTION()
    void SetTargetActor(AActor* NewTargetActor);

    UFUNCTION()
    AActor* GetTargetActor();

private:
    AActor* TargetActor;

protected:
    virtual void SynchronizeProperties() override;

    UFUNCTION()
    void OnButtonClicked();

	
};
