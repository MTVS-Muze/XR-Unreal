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
#include "Runtime/UMG/Public/Components/EditableText.h"
#include "Runtime/UMG/Public/Components/Widget.h"
#include "OSY_LightBaseActor.h"
#include "OSY_PropBaseActor.h"
#include "Runtime/UMG/Public/Components/ExpandableArea.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"


void UOSY_OutLinerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 액터 정보를 UI에 표시
    DisplayActorInfo();

    UExpandableArea* ExpandableArea = Cast<UExpandableArea>(GetWidgetFromName(TEXT("YourExpandableAreaName")));

    
   

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
        if (Actor->IsA(AOSY_LightBaseActor::StaticClass()))
        {
            // AOSY_LightBaseActor 클래스의 액터는 vb_Category1에 버튼을 추가합니다.
            AddButton(Actor, ea_Category1, vb_Category1);
        }
        else if (Actor->IsA(AOSY_PropBaseActor::StaticClass()))
        {
            AddButton(Actor,ea_Category2,vb_Category2);
        }
        // 필요한 경우 다른 클래스에 대한 처리를 추가합니다.
    }
}

void UOSY_OutLinerWidget::AddButton(AActor* Actor, UExpandableArea* Expandable, UVerticalBox* Vertical)
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
        UE_LOG(LogTemp, Warning, TEXT("Actor:%s"), *ActorName);

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
        Vertical->AddChild(Button);
        sb_OutLiner->AddChild(Expandable);
        
        Button->OnButtonClickedDelegate.AddDynamic(this, &UOSY_OutLinerWidget::OnButtonClicked);
    }
}

void UOSY_OutLinerWidget::OnButtonClicked(AActor* Actor)
{

    if (Actor->IsA(AOSY_LightBaseActor::StaticClass()))
    {
        CurrentActor = Actor;
        // 액터의 이름과 위치를 가져와서 텍스트 블록에 설정합니다.
        tb_NameTextBlock->SetText(FText::FromString(Actor->GetName()));

        edit_LocationX->SetText(FText::AsNumber(Actor->GetActorLocation().X));
        edit_LocationY->SetText(FText::AsNumber(Actor->GetActorLocation().Y));
        edit_LocationZ->SetText(FText::AsNumber(Actor->GetActorLocation().Z));

        edit_LocationX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationXChanged);
        edit_LocationY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationYChanged);
        edit_LocationZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationZChanged);

        edit_RotationRoll->SetText(FText::AsNumber(Actor->GetActorRotation().Roll));
        edit_RotationPitch->SetText(FText::AsNumber(Actor->GetActorRotation().Pitch));
        edit_RotationYaw->SetText(FText::AsNumber(Actor->GetActorRotation().Yaw));

        edit_RotationRoll->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionRollChanged);
        edit_RotationPitch->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionPitchChanged);
        edit_RotationYaw->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotationYawChanged);

        edit_ScaleX->SetText(FText::AsNumber(Actor->GetActorScale().X));
        edit_ScaleY->SetText(FText::AsNumber(Actor->GetActorScale().Y));
        edit_ScaleZ->SetText(FText::AsNumber(Actor->GetActorScale().Z));

        edit_ScaleX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLScaleXChanged);
        edit_ScaleY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleYChanged);
        edit_ScaleZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleZChanged);
    }
    else if (Actor->IsA(AOSY_PropBaseActor::StaticClass()))
    {
        CurrentActor = Actor;
        // 액터의 이름과 위치를 가져와서 텍스트 블록에 설정합니다.
        tb_NameTextBlock->SetText(FText::FromString(Actor->GetName()));

        edit_LocationX->SetText(FText::AsNumber(Actor->GetActorLocation().X));
        edit_LocationY->SetText(FText::AsNumber(Actor->GetActorLocation().Y));
        edit_LocationZ->SetText(FText::AsNumber(Actor->GetActorLocation().Z));

        edit_LocationX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationXChanged);
        edit_LocationY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationYChanged);
        edit_LocationZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationZChanged);

        edit_RotationRoll->SetText(FText::AsNumber(Actor->GetActorRotation().Roll));
        edit_RotationPitch->SetText(FText::AsNumber(Actor->GetActorRotation().Pitch));
        edit_RotationYaw->SetText(FText::AsNumber(Actor->GetActorRotation().Yaw));

        edit_RotationRoll->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionRollChanged);
        edit_RotationPitch->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionPitchChanged);
        edit_RotationYaw->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotationYawChanged);

        edit_ScaleX->SetText(FText::AsNumber(Actor->GetActorScale().X));
        edit_ScaleY->SetText(FText::AsNumber(Actor->GetActorScale().Y));
        edit_ScaleZ->SetText(FText::AsNumber(Actor->GetActorScale().Z));

        edit_ScaleX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLScaleXChanged);
        edit_ScaleY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleYChanged);
        edit_ScaleZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleZChanged);
    }

}

#pragma region Location
void UOSY_OutLinerWidget::OnLocationXChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) // CurrentActor는 현재 선택된 액터를 가리키는 멤버 변수입니다.
    {
        FVector NewLocation = CurrentActor->GetActorLocation();
        NewLocation.X = FCString::Atof(*NewText.ToString()); // 새로운 X 좌표를 파싱하여 설정
        CurrentActor->SetActorLocation(NewLocation);
    }
}

void UOSY_OutLinerWidget::OnLocationYChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) // CurrentActor는 현재 선택된 액터를 가리키는 멤버 변수입니다.
    {
        FVector NewLocation = CurrentActor->GetActorLocation();
        NewLocation.Y = FCString::Atof(*NewText.ToString()); // 새로운 X 좌표를 파싱하여 설정
        CurrentActor->SetActorLocation(NewLocation);
    }
}

void UOSY_OutLinerWidget::OnLocationZChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) // CurrentActor는 현재 선택된 액터를 가리키는 멤버 변수입니다.
    {
        FVector NewLocation = CurrentActor->GetActorLocation();
        NewLocation.Z = FCString::Atof(*NewText.ToString()); // 새로운 X 좌표를 파싱하여 설정
        CurrentActor->SetActorLocation(NewLocation);
    }
}
#pragma endregion

#pragma region Rotation
void UOSY_OutLinerWidget::OnRotaionRollChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) 
    {
        FRotator NewRotation = CurrentActor->GetActorRotation();
        NewRotation.Roll = FCString::Atof(*NewText.ToString()); 
        CurrentActor->SetActorRotation(NewRotation);
    }
}

void UOSY_OutLinerWidget::OnRotaionPitchChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor)
    {
        FRotator NewRotation = CurrentActor->GetActorRotation();
        NewRotation.Pitch = FCString::Atof(*NewText.ToString());
        CurrentActor->SetActorRotation(NewRotation);
    }
}

void UOSY_OutLinerWidget::OnRotationYawChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor)
    {
        FRotator NewRotation = CurrentActor->GetActorRotation();
        NewRotation.Yaw = FCString::Atof(*NewText.ToString());
        CurrentActor->SetActorRotation(NewRotation);
    }
}

#pragma endregion

#pragma region Scale
void UOSY_OutLinerWidget::OnLScaleXChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) 
    {
        FVector NewScale = CurrentActor->GetActorScale3D();
        NewScale.X = FCString::Atof(*NewText.ToString()); 
        CurrentActor->SetActorScale3D(NewScale);
    }
}

void UOSY_OutLinerWidget::OnScaleYChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor)
    {
        FVector NewScale = CurrentActor->GetActorScale3D();
        NewScale.Y = FCString::Atof(*NewText.ToString());
        CurrentActor->SetActorScale3D(NewScale);
    }
}

void UOSY_OutLinerWidget::OnScaleZChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor)
    {
        FVector NewScale = CurrentActor->GetActorScale3D();
        NewScale.Z = FCString::Atof(*NewText.ToString());
        CurrentActor->SetActorScale3D(NewScale);
    }
}


#pragma endregion

