// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KJS_MuzePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API AKJS_MuzePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	int32 ColorIndex;

	UPROPERTY(Replicated)
	int32 HatIndex;

	UPROPERTY(Replicated)
	int32 GlassIndex;

	UPROPERTY(Replicated)
	int32 TieIndex;


	UFUNCTION(Server, Reliable)
	void ServerSetColorIndex(int32 NewIndex);

	UFUNCTION(Server, Reliable)
	void ServerSetHatIndex(int32 NewIndex);

	UFUNCTION(Server, Reliable)
	void ServerSetGlassIndex(int32 NewIndex);

	UFUNCTION(Server, Reliable)
	void ServerSetTieIndex(int32 NewIndex);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
