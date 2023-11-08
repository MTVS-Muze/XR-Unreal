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

    // ���� ������ UI�� ǥ��
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

    // ScrollBox�� Ŭ�����մϴ�.
    if (sb_OutLiner)
    {
        sb_OutLiner->ClearChildren();
    }

    for (AActor* Actor : ActorList)
    {
        // ������ �̸��� Ÿ���� �����ɴϴ�.
        ActorName = Actor->GetName();
        ActorType = Actor->GetClass()->GetName();
        

        // ���ο� ��ư�� �����մϴ�.
        Button = NewObject<UOSY_OutLinerButton>(this);
        if (Button)
        {
            // ��ư�� Ŭ�� �̺�Ʈ�� �߰��մϴ�.
            Button->SetTargetActor(Actor);
        UE_LOG(LogTemp,Warning,TEXT("Actor:%s"),*ActorName);

            // ��ư�� ���͸� �ʿ� �߰��մϴ�.
            ButtonToActorMap.Add(Button, Actor);

            // ��ư�� �ؽ�Ʈ ����� �߰��մϴ�.
            UTextBlock* TextBlock = NewObject<UTextBlock>(this);
            if (TextBlock)
            {
                // �ؽ�Ʈ ����� �ؽ�Ʈ�� �����մϴ�.
               
               TextBlock->SetJustification(ETextJustify::Left);
                TextBlock->SetText(FText::FromString(ActorName + ": " + ActorType));

                // �ؽ�Ʈ ����� ��ư�� �ڽ����� �߰��մϴ�.
                Button->AddChild(TextBlock);
            }

            // ��ư�� ScrollBox�� �߰��մϴ�.
            sb_OutLiner->AddChild(Button);
        }
    }
}
//----------------------------------------




