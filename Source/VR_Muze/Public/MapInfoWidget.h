// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UMapInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UEditableText* edit_Title;

	FString title;

	 UFUNCTION()
    void TitleCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UEditableText* edit_Info;
	
	FString info;
	 UFUNCTION()
    void InfoCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY()
	class UOSY_GameInstance* gi;



	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
    class UComboBoxString* scb_SongList;

    UFUNCTION()
    void HandleOnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	FString song;
	FString singer;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=CreateSettings)
	class UButton* btn_GoCreateMap;

	UFUNCTION()
	void GoCreateMap();




};
