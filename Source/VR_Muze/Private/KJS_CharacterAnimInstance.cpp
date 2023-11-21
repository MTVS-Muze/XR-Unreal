// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_CharacterAnimInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UKJS_CharacterAnimInstance::UKJS_CharacterAnimInstance()
{
	CurrentLevelName = FString();
}

void UKJS_CharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    UWorld* World = GetWorld();
    if (World)
    {
        CurrentLevelName = UGameplayStatics::GetCurrentLevelName(World);
    }
}

bool UKJS_CharacterAnimInstance::IsInLevel(const FString& LevelName) const
{
    return CurrentLevelName == LevelName;
}
