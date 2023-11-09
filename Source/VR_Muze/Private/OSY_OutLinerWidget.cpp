// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_OutLinerWidget.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"
#include "Runtime/Slate/Public/Framework/Application/SlateApplication.h"
#include "OSY_OutLinerButton.h"
#include "Runtime/UMG/Public/Components/Widget.h"

void UOSY_OutLinerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 액터 정보를 UI에 표시
    DisplayActorInfo();

 
}

TArray<AActor*> UOSY_OutLinerWidget::GetAllActorsInWorld()
{
    TArray<AActor*> AllActors;
    for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        AllActors.Add(*ActorItr);
    }
    return AllActors;
}

void UOSY_OutLinerWidget::DisplayActorInfo()
{
    TArray<AActor*> ActorList = GetAllActorsInWorld();

    // ScrollBox를 클리어합니다.
    if (sb_OutLiner)
    {
        sb_OutLiner->ClearChildren();
    }

    for (AActor* Actor : ActorList)
    {
        // 액터의 이름과 타입을 가져옵니다.
        ActorName = Actor->GetName();
        ActorType = Actor->GetClass()->GetName();
        

        // 새로운 버튼을 생성합니다.
        Button = NewObject<UOSY_OutLinerButton>(this);
        if (Button)
        {
            // 버튼의 클릭 이벤트를 추가합니다.
            Button->SetTargetActor(Actor);
        UE_LOG(LogTemp,Warning,TEXT("Actor:%s"),*ActorName);

            // 버튼과 액터를 맵에 추가합니다.
            ButtonToActorMap.Add(Button, Actor);

            // 버튼에 텍스트 블록을 추가합니다.
            UTextBlock* TextBlock = NewObject<UTextBlock>(this);
            if (TextBlock)
            {
                // 텍스트 블록의 텍스트를 설정합니다.
               
               TextBlock->SetJustification(ETextJustify::Left);
                TextBlock->SetText(FText::FromString(ActorName + ": " + ActorType));

                // 텍스트 블록을 버튼의 자식으로 추가합니다.
                Button->AddChild(TextBlock);
            }

            // 버튼을 ScrollBox에 추가합니다.
            sb_OutLiner->AddChild(Button);
        }
    }
}
//----------------------------------------




