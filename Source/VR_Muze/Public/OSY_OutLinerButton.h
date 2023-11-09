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

    // Ŭ���� ��ư�� ����Ű�� ���͸� �����ϰ� ��ȯ�ϴ� �Լ��� �߰��մϴ�.
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
