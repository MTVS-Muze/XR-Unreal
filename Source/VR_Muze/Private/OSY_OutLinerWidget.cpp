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
#include "Runtime/Engine/Classes/Components/LightComponent.h"
#include "Math/Color.h"
#include "Runtime/Engine/Classes/Components/DirectionalLightComponent.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"


void UOSY_OutLinerWidget::NativeConstruct()
{
    Super::NativeConstruct();

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

    if (sb_OutLiner)
    {
        sb_OutLiner->ClearChildren();
    }

    for (AActor* Actor : ActorList)
    {
        if (Actor->IsA(AOSY_LightBaseActor::StaticClass()))
        {
            AddButton(Actor, ea_Category1, vb_Category1);
        }
        else if (Actor->IsA(AOSY_PropBaseActor::StaticClass()))
        {
            AddButton(Actor,ea_Category2,vb_Category2);
        }
    }
}

void UOSY_OutLinerWidget::AddButton(AActor* Actor, UExpandableArea* Expandable, UVerticalBox* Vertical)
{
    ActorName = Actor->GetName();
    ActorType = Actor->GetClass()->GetName();

    Button = NewObject<UOSY_OutLinerButton>(this);
    if (Button)
    {
        Button->SetTargetActor(Actor);
        UE_LOG(LogTemp, Warning, TEXT("Actor:%s"), *ActorName);

        ButtonToActorMap.Add(Button, Actor);

        UTextBlock* TextBlock = NewObject<UTextBlock>(this);
        if (TextBlock)
        {

            TextBlock->SetJustification(ETextJustify::Left);
            TextBlock->SetText(FText::FromString(ActorName + ": " + ActorType));

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
        

        #pragma region Location

        edit_LocationX->SetText(FText::AsNumber(Actor->GetActorLocation().X));
        edit_LocationY->SetText(FText::AsNumber(Actor->GetActorLocation().Y));
        edit_LocationZ->SetText(FText::AsNumber(Actor->GetActorLocation().Z));

        edit_LocationX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationXChanged);
        edit_LocationY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationYChanged);
        edit_LocationZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationZChanged);
#pragma endregion
        #pragma region Rotation
        edit_RotationRoll->SetText(FText::AsNumber(Actor->GetActorRotation().Roll));
        edit_RotationPitch->SetText(FText::AsNumber(Actor->GetActorRotation().Pitch));
        edit_RotationYaw->SetText(FText::AsNumber(Actor->GetActorRotation().Yaw));

        edit_RotationRoll->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionRollChanged);
        edit_RotationPitch->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionPitchChanged);
        edit_RotationYaw->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotationYawChanged);
#pragma endregion
        #pragma region Scale
        edit_ScaleX->SetText(FText::AsNumber(Actor->GetActorScale().X));
        edit_ScaleY->SetText(FText::AsNumber(Actor->GetActorScale().Y));
        edit_ScaleZ->SetText(FText::AsNumber(Actor->GetActorScale().Z));

        edit_ScaleX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleXChanged);
        edit_ScaleY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleYChanged);
        edit_ScaleZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleZChanged);
#pragma endregion     
        #pragma region LightColor
        
        if(Actor->GetComponentByClass(UDirectionalLightComponent::StaticClass()))
        {
            UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(Actor->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
            if (LightComponent)
            {

				edit_LightR->SetText(FText::AsNumber(LightComponent->LightColor.R));
                edit_LightG->SetText(FText::AsNumber(LightComponent->LightColor.G));
                edit_LightB->SetText(FText::AsNumber(LightComponent->LightColor.B));

				edit_LightR->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightRChanged);
				edit_LightG->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightGChanged);
				edit_LightB->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightBChanged);
            }
        }
        else if (Actor->GetComponentByClass(UPointLightComponent::StaticClass()))
        {
            UPointLightComponent* LightComponent = Cast<UPointLightComponent>(Actor->GetComponentByClass(UPointLightComponent::StaticClass()));
            if (LightComponent)
            {

                edit_LightR->SetText(FText::AsNumber(LightComponent->LightColor.R));
                edit_LightG->SetText(FText::AsNumber(LightComponent->LightColor.G));
                edit_LightB->SetText(FText::AsNumber(LightComponent->LightColor.B));

                edit_LightR->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightRChanged);
                edit_LightG->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightGChanged);
                edit_LightB->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightBChanged);
            }
        }
        else if (Actor->GetComponentByClass(USpotLightComponent::StaticClass()))
        {
            USpotLightComponent* LightComponent = Cast<USpotLightComponent>(Actor->GetComponentByClass(USpotLightComponent::StaticClass()));
            if (LightComponent)
            {

                edit_LightR->SetText(FText::AsNumber(LightComponent->LightColor.R));
                edit_LightG->SetText(FText::AsNumber(LightComponent->LightColor.G));
                edit_LightB->SetText(FText::AsNumber(LightComponent->LightColor.B));

                edit_LightR->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightRChanged);
                edit_LightG->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightGChanged);
                edit_LightB->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLightBChanged);
            }
        }
        #pragma endregion
    }
    else if (Actor->IsA(AOSY_PropBaseActor::StaticClass()))
    {
        CurrentActor = Actor;
        
        #pragma region Location
        edit_LocationX->SetText(FText::AsNumber(Actor->GetActorLocation().X));
        edit_LocationY->SetText(FText::AsNumber(Actor->GetActorLocation().Y));
        edit_LocationZ->SetText(FText::AsNumber(Actor->GetActorLocation().Z));

        edit_LocationX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationXChanged);
        edit_LocationY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationYChanged);
        edit_LocationZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnLocationZChanged);
        #pragma endregion

        #pragma region Rotation
        edit_RotationRoll->SetText(FText::AsNumber(Actor->GetActorRotation().Roll));
        edit_RotationPitch->SetText(FText::AsNumber(Actor->GetActorRotation().Pitch));
        edit_RotationYaw->SetText(FText::AsNumber(Actor->GetActorRotation().Yaw));

        edit_RotationRoll->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionRollChanged);
        edit_RotationPitch->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotaionPitchChanged);
        edit_RotationYaw->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnRotationYawChanged);
         
        #pragma endregion

        #pragma region Scale
        edit_ScaleX->SetText(FText::AsNumber(Actor->GetActorScale().X));
        edit_ScaleY->SetText(FText::AsNumber(Actor->GetActorScale().Y));
        edit_ScaleZ->SetText(FText::AsNumber(Actor->GetActorScale().Z));

        edit_ScaleX->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleXChanged);
        edit_ScaleY->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleYChanged);
        edit_ScaleZ->OnTextCommitted.AddDynamic(this, &UOSY_OutLinerWidget::OnScaleZChanged);
        #pragma endregion

    }
}

#pragma region Location
void UOSY_OutLinerWidget::OnLocationXChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) 
    {
        FVector NewLocation = CurrentActor->GetActorLocation();
        NewLocation.X = FCString::Atof(*NewText.ToString()); 
        CurrentActor->SetActorLocation(NewLocation);
    }
}

void UOSY_OutLinerWidget::OnLocationYChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) 
    {
        FVector NewLocation = CurrentActor->GetActorLocation();
        NewLocation.Y = FCString::Atof(*NewText.ToString()); 
        CurrentActor->SetActorLocation(NewLocation);
    }
}

void UOSY_OutLinerWidget::OnLocationZChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor) 
    {
        FVector NewLocation = CurrentActor->GetActorLocation();
        NewLocation.Z = FCString::Atof(*NewText.ToString()); 
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
void UOSY_OutLinerWidget::OnScaleXChanged(const FText& NewText, ETextCommit::Type CommitType)
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

#pragma region LightColor
void UOSY_OutLinerWidget::OnLightRChanged(const FText& NewText, ETextCommit::Type CommitType)
{
	if (CurrentActor)
	{
        if (CurrentActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()))
        {
            UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(CurrentActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.R = NewRValue;
                LightComponent->SetLightColor(LightColor); 
            }
        }

        else if (CurrentActor->GetComponentByClass(UPointLightComponent::StaticClass()))
        {
            UPointLightComponent* LightComponent = Cast<UPointLightComponent>(CurrentActor->GetComponentByClass(UPointLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.R = NewRValue; 
                LightComponent->SetLightColor(LightColor); 
            }
        }
        else if (CurrentActor->GetComponentByClass(USpotLightComponent::StaticClass()))
        {
            USpotLightComponent* LightComponent = Cast<USpotLightComponent>(CurrentActor->GetComponentByClass(USpotLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.R = NewRValue; 
                LightComponent->SetLightColor(LightColor);
            }
        }
	}
}

void UOSY_OutLinerWidget::OnLightGChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor)
    {
        if (CurrentActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()))
        {
            UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(CurrentActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.G = NewRValue; 
                LightComponent->SetLightColor(LightColor); 
            }
        }

        else if (CurrentActor->GetComponentByClass(UPointLightComponent::StaticClass()))
        {
            UPointLightComponent* LightComponent = Cast<UPointLightComponent>(CurrentActor->GetComponentByClass(UPointLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.G = NewRValue; 
                LightComponent->SetLightColor(LightColor);
            }
        }
        else if (CurrentActor->GetComponentByClass(USpotLightComponent::StaticClass()))
        {
            USpotLightComponent* LightComponent = Cast<USpotLightComponent>(CurrentActor->GetComponentByClass(USpotLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.G = NewRValue;
                LightComponent->SetLightColor(LightColor); 
            }
        }
    }
}

void UOSY_OutLinerWidget::OnLightBChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CurrentActor)
    {
        if (CurrentActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()))
        {
            UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(CurrentActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.B = NewRValue; 
                LightComponent->SetLightColor(LightColor); 
            }
        }

        else if (CurrentActor->GetComponentByClass(UPointLightComponent::StaticClass()))
        {
            UPointLightComponent* LightComponent = Cast<UPointLightComponent>(CurrentActor->GetComponentByClass(UPointLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.B = NewRValue; 
                LightComponent->SetLightColor(LightColor);
            }
        }
        else if (CurrentActor->GetComponentByClass(USpotLightComponent::StaticClass()))
        {
            USpotLightComponent* LightComponent = Cast<USpotLightComponent>(CurrentActor->GetComponentByClass(USpotLightComponent::StaticClass()));
            if (LightComponent)
            {
                FLinearColor LightColor = LightComponent->LightColor;
                float NewRValue = FCString::Atof(*NewText.ToString()); 
                LightColor.B = NewRValue; 
                LightComponent->SetLightColor(LightColor); 
            }
        }
    }
}


#pragma endregion

