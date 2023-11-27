// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_SJGameModeBase.h"
#include "OSY_GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_HttpRequestActor.h"
#include "OSY_TImeActor.h"

AOSY_SJGameModeBase::AOSY_SJGameModeBase()
{

}

void AOSY_SJGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AOSY_SJGameModeBase::Tick(float DeltaTime)
{
	gi = Cast<UOSY_GameInstance>(GetGameInstance());
	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

	TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));

}
