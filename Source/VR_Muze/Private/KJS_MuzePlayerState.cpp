// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_MuzePlayerState.h"
#include "MyCharacter.h"

void AKJS_MuzePlayerState::ServerSetColorIndex_Implementation(int32 NewIndex)
{
	MulticastSetColorIndex(NewIndex);
}

void AKJS_MuzePlayerState::ServerSetHatIndex_Implementation(int32 NewIndex)
{
	MulticastSetHatIndex(NewIndex);
}

void AKJS_MuzePlayerState::ServerSetGlassIndex_Implementation(int32 NewIndex)
{
	MulticastSetGlassIndex(NewIndex);
}

void AKJS_MuzePlayerState::ServerSetTieIndex_Implementation(int32 NewIndex)
{
	MulticastrSetTieIndex(NewIndex);
}

void AKJS_MuzePlayerState::MulticastSetColorIndex_Implementation(int32 NewIndex)
{
	ColorIndex = NewIndex;
}

void AKJS_MuzePlayerState::MulticastSetHatIndex_Implementation(int32 NewIndex)
{
	HatIndex = NewIndex;
}

void AKJS_MuzePlayerState::MulticastSetGlassIndex_Implementation(int32 NewIndex)
{
	GlassIndex = NewIndex;
}

void AKJS_MuzePlayerState::MulticastrSetTieIndex_Implementation(int32 NewIndex)
{
	GlassIndex = NewIndex;
}

void AKJS_MuzePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AKJS_MuzePlayerState, ColorIndex);
	DOREPLIFETIME(AKJS_MuzePlayerState, HatIndex);
	DOREPLIFETIME(AKJS_MuzePlayerState, GlassIndex);
	DOREPLIFETIME(AKJS_MuzePlayerState, TieIndex);
}
