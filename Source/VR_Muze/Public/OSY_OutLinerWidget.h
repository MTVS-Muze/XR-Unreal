// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "OSY_OutLinerWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_OutLinerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UScrollBox* sb_OutLiner;

    // 월드에 있는 모든 액터를 가져오는 함수
    TArray<AActor*> GetAllActorsInWorld();

    // 액터 정보를 UI에 표시하는 함수
    UFUNCTION()
    void DisplayActorInfo();

    UFUNCTION()
    void AddButton(AActor* Actor, UExpandableArea* Expandable,UVerticalBox* Vertical);
    //UFUNCTION()
    //void OnButtonClicked();

   

    UPROPERTY(EditAnywhere,Category= MySettings)
    FString ActorName;
    UPROPERTY(EditAnywhere,Category= MySettings)
    FString ActorType;
    UPROPERTY(EditAnywhere,Category= MySettings)
    class UOSY_OutLinerButton* Button;

    UPROPERTY(EditAnywhere,Category= MySettings)
    TMap<UButton*, AActor*> ButtonToActorMap;

    UFUNCTION()
    void OnButtonClicked(AActor* Actor);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* tb_NameTextBlock;

     UPROPERTY()
    AActor* CurrentActor; 

#pragma region OutLineUI
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UExpandableArea* ea_Category1;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UExpandableArea* ea_Category2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* vb_Category1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* vb_Category2;

#pragma endregion 


#pragma region Location

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_LocationX;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_LocationY;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_LocationZ;

    UFUNCTION()
    void OnLocationXChanged(const FText& NewText, ETextCommit::Type CommitType);

    UFUNCTION()
    void OnLocationYChanged(const FText& NewText, ETextCommit::Type CommitType);

     UFUNCTION()
    void OnLocationZChanged(const FText& NewText, ETextCommit::Type CommitType);

    
#pragma endregion

#pragma region Rotation

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_RotationRoll;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_RotationPitch;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_RotationYaw;

     UFUNCTION()
    void OnRotaionRollChanged(const FText& NewText, ETextCommit::Type CommitType);

     UFUNCTION()
    void OnRotaionPitchChanged(const FText& NewText, ETextCommit::Type CommitType);

     UFUNCTION()
    void OnRotationYawChanged(const FText& NewText, ETextCommit::Type CommitType);

#pragma endregion

#pragma region Scale
      UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_ScaleX;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_ScaleY;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_ScaleZ;

    UFUNCTION()
    void OnScaleXChanged(const FText& NewText, ETextCommit::Type CommitType);

    UFUNCTION()
    void OnScaleYChanged(const FText& NewText, ETextCommit::Type CommitType);

     UFUNCTION()
    void OnScaleZChanged(const FText& NewText, ETextCommit::Type CommitType);
#pragma endregion

#pragma region LightColor


    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_LightR;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_LightG;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UEditableText* edit_LightB;

      UFUNCTION()
    void OnLightRChanged(const FText& NewText, ETextCommit::Type CommitType);

    UFUNCTION()
    void OnLightGChanged(const FText& NewText, ETextCommit::Type CommitType);

     UFUNCTION()
    void OnLightBChanged(const FText& NewText, ETextCommit::Type CommitType);
#pragma endregion
  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UButton* btn_test;

    UFUNCTION()
    void testFunc();
};
	

