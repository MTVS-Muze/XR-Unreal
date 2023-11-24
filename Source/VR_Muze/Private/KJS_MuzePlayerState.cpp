// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_MuzePlayerState.h"

void AKJS_MuzePlayerState::ServerSetColorIndex_Implementation(int32 NewIndex)
{
	ColorIndex = NewIndex;
}

void AKJS_MuzePlayerState::ServerSetHatIndex_Implementation(int32 NewIndex)
{
	HatIndex = NewIndex;
}

void AKJS_MuzePlayerState::ServerSetGlassIndex_Implementation(int32 NewIndex)
{
	GlassIndex = NewIndex;
}

void AKJS_MuzePlayerState::ServerSetTieIndex_Implementation(int32 NewIndex)
{
	TieIndex = NewIndex;
}

void AKJS_MuzePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AKJS_MuzePlayerState, ColorIndex);
	DOREPLIFETIME(AKJS_MuzePlayerState, HatIndex);
	DOREPLIFETIME(AKJS_MuzePlayerState, GlassIndex);
	DOREPLIFETIME(AKJS_MuzePlayerState, TieIndex);
}
