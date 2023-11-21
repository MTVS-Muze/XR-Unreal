// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KJS_CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UKJS_CharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UKJS_CharacterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = Animation)
    bool IsInLevel(const FString& LevelName) const;

public:
	FString CurrentLevelName;
	
};
