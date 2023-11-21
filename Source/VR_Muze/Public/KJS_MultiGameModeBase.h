// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "KJS_MultiGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AKJS_MultiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	APlayerStart* SpawnPlayerStart(FVector Location);


	UPROPERTY()
	class UOSY_GameInstance* gi;

private:
	TArray<APlayerStart*> UsedPlayerStarts;

	
};