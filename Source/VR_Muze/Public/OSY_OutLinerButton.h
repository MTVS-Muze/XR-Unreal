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
    // Ŭ���� ��ư�� ����Ű�� ���͸� �����ϰ� ��ȯ�ϴ� �Լ��� �߰��մϴ�.
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
