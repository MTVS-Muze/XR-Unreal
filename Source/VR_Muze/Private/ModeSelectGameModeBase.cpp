// Fill out your copyright notice in the Description page of Project Settings.


#include "ModeSelectGameModeBase.h"
#include "MainWidget.h"
#include "OSY_HttpRequestActor.h"
#include "OSY_GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AModeSelectGameModeBase::AModeSelectGameModeBase()
{
}

void AModeSelectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    ModeSelectUI = CreateWidget<UMainWidget>(GetWorld(), ModeSelectWidget);
    if (ModeSelectUI != nullptr)
    {
        ModeSelectUI->AddToViewport();

    }
    gi = Cast<UOSY_GameInstance>(GetGameInstance());
    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));
   
   
    GetMemberInfo();


   

}

void AModeSelectGameModeBase::GetMemberInfo()
{
UE_LOG(LogTemp,Warning,TEXT("haigo"));
        if (HttpActor != nullptr)
        {
            HttpActor->SendRequest(gi->MemberInfourl);
            HttpActor->SendRequest(gi->AllMap);
        }
    
}

