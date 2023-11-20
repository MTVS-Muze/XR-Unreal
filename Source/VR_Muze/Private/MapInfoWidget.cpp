// Fill out your copyright notice in the Description page of Project Settings.


#include "MapInfoWidget.h"
#include "Runtime/UMG/Public/Components/EditableText.h"
#include "OSY_GameInstance.h"
#include "Runtime/UMG/Public/Components/ComboBoxString.h"
#include "Runtime/UMG/Public/Components/Button.h"

void UMapInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	if (btn_GoCreateMap)
	{
		btn_GoCreateMap->OnClicked.AddDynamic(this,&UMapInfoWidget::GoCreateMap);
	}

	if (edit_Title)
	{
		edit_Title->OnTextCommitted.AddDynamic(this, &UMapInfoWidget::TitleCommitted);
	}
	if (edit_Info)
	{
		edit_Info->OnTextCommitted.AddDynamic(this, &UMapInfoWidget::InfoCommitted);
	}
	if (scb_SongList)
	{

		scb_SongList->AddOption("A");
		scb_SongList->AddOption("B");
		scb_SongList->AddOption("C");

		scb_SongList->OnSelectionChanged.AddDynamic(this, &UMapInfoWidget::HandleOnSelectionChanged);
	}
}

void UMapInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

}

void UMapInfoWidget::TitleCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	 title = Text.ToString();
	 if (gi != nullptr)
	 {
		 gi->title=title;
	 }
}

void UMapInfoWidget::InfoCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	info= Text.ToString();
	if (gi != nullptr)
	{
		gi->info = info;
	}
}

void UMapInfoWidget::HandleOnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectedItem == "A") 
	{
		song = "Song A";
		singer = "Singer A";
		gi->song= song;
		gi->singer	= singer;
	}
	else if (SelectedItem == "B") 
	{
		song = "Song B";
		singer = "Singer B";
		gi->song = song;
		gi->singer = singer;
	}
	else if (SelectedItem == "C") 
	{
		song = "Song C";
		singer = "Singer C";
		gi->song = song;
		gi->singer = singer;
	}
}

void UMapInfoWidget::GoCreateMap()
{
	if (title.IsEmpty())
	{
		return;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("SIBURe"));
	}
	
}
