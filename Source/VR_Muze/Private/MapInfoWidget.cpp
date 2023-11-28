// Fill out your copyright notice in the Description page of Project Settings.


#include "MapInfoWidget.h"
#include "Runtime/UMG/Public/Components/EditableText.h"
#include "OSY_GameInstance.h"
#include "Runtime/UMG/Public/Components/ComboBoxString.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UMapInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	if (btn_GoCreateMap)
	{
		btn_GoCreateMap->OnClicked.AddDynamic(this,&UMapInfoWidget::GoCreateMap);
	}
	btn_Back2->OnClicked.AddDynamic(this,&UMapInfoWidget::GoMain);
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
		scb_SongList->AddOption("Deep_Future_Garage");
		scb_SongList->AddOption("LoFI_Chill");
		scb_SongList->AddOption("Ocean_in_Paris");
		scb_SongList->AddOption("Relaxing");
		scb_SongList->AddOption("Titanium");

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

	if (SelectedItem == "Deep_Future_Garage") 
	{
		song = "Deep_Future_Garage";
		singer = "Coma-Media";
		gi->song= song;
		gi->singer	= singer;
	}
	else if (SelectedItem == "LoFi_Chill") 
	{
		song = "LoFI_Chill";
		singer = "BoDleasons";
		gi->song = song;
		gi->singer = singer;
	}
	else if (SelectedItem == "ocean_In_Paris") 
	{
		song = "ocean_In_Paris";
		singer = "Pumpupthemind";
		gi->song = song;
		gi->singer = singer;
	}
	else if (SelectedItem == "Relaxing")
	{
		song = "Relaxing";
		singer = "lemonmusicstudio";
		gi->song = song;
		gi->singer = singer;
	}
	else if (SelectedItem == "Titanium")
	{
		song = "Titanium";
		singer = "AlishaMusic";
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
		FName LevelName = "3_3CreateMap";

		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}
	
}

void UMapInfoWidget::GoMain()
{
	FName LevelName = "2_ViewLevel";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}
