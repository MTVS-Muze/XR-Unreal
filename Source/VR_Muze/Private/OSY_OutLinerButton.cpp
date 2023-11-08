// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_OutLinerButton.h"

void UOSY_OutLinerButton::SetTargetActor(AActor* NewTargetActor)
{
    TargetActor = NewTargetActor;
}

AActor* UOSY_OutLinerButton::GetTargetActor()
{
    return TargetActor;
}

void UOSY_OutLinerButton::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    OnClicked.AddDynamic(this, &UOSY_OutLinerButton::OnButtonClicked);
}

void UOSY_OutLinerButton::OnButtonClicked()
{
    if (TargetActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Clicked actor: %s"), *TargetActor->GetName());
    }
}