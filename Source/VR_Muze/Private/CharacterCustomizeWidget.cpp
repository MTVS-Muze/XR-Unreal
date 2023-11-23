// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCustomizeWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstance.h"
#include "MyCharacter.h"
#include "OSY_GameInstance.h"
#include "OSY_HttpRequestActor.h"

void UCharacterCustomizeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	APawn* Pawn = PlayerController->GetPawn();
	player = Cast<AMyCharacter>(Pawn);

	gi = Cast<UOSY_GameInstance>(GetGameInstance());
	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

	btn_IntoBox->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_IntoBox);
	btn_IntoCustomize->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_IntoCustomize);
	///////////////////////////////////////////////////
	btn_Save->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_CustomizeSave);
	btn_Back->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_BackSelect);
	///////////////////////////////////////////////////
	btn_Black->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorBlack);
	btn_White->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorWhite);
	btn_SkyBlue->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorSkyBlue);
	btn_Pink->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorPink);
	btn_Yellow->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorYellow);
	btn_Green->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorGreen);
	btn_DeepYellow->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorDeepYellow);
	btn_Violet->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorViolet);
	btn_Coral->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorCoral);
	btn_Navy->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::SwitchColorNavy);
	///////////////////////////////////////////////////
	btn_Hat->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_Hat);
	btn_Glass->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_Glass);
	btn_Tie->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::OnClickedbtn_Tie);
	////////////////////////////////////////////////////
	btn_Glass0->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass0);
	btn_Glass1->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass1);
	btn_Glass2->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass2);
	btn_Glass3->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass3);
	btn_Glass4->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass4);
	btn_Glass5->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass5);
	btn_Glass6->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearGlass6);
	//////////////////////////////////////////////////////
	btn_Hat1->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearHat1);
	btn_Hat2->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearHat2);
	/////////////////////////////////////////////////////////
	btn_Tie1->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearTie1);
	btn_Tie2->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearTie2);
	btn_Tie3->OnClicked.AddDynamic(this, &UCharacterCustomizeWidget::WearTie3);

}

void UCharacterCustomizeWidget::SwitchCanvas(int32 index)
{
	ws_CharacterCustomize->SetActiveWidgetIndex(index);
}

void UCharacterCustomizeWidget::OnClickedbtn_IntoBox()
{
	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	FName LevelName = "2_ViewLevel";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UCharacterCustomizeWidget::OnClickedbtn_IntoCustomize()
{
	SwitchCanvas(1);
}

void UCharacterCustomizeWidget::OnClickedbtn_CustomizeSave()
{
	//서버에 정보 보내기
	if (HttpActor != nullptr)
	{
		HttpActor->PostRequest(gi->CustomURL,JsonStringPost);
		//CustomURL 뒤에 JSonString 형태의 데이터 넘기면됨
	}
}

void UCharacterCustomizeWidget::OnClickedbtn_BackSelect()
{
	SwitchCanvas(0);
}


void UCharacterCustomizeWidget::SwitchColorBlack()
{
	
	color=0;
	gi->color=color;
	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorWhite()
{
	color=1;
	gi->color = color;
	
	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorSkyBlue()
{
	color=2;
	gi->color = color;
	
	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorPink()
{
	color=3;
	player->SwitchBodyColor(color);
	gi->color = color;

}

void UCharacterCustomizeWidget::SwitchColorYellow()
{
	color=4;
	gi->color = color;
	
	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorGreen()
{
	color=5;
	gi->color = color;

	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorDeepYellow()
{
	color=6;
	gi->color = color;

	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorViolet()
{
	color=7;
	gi->color = color;

	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorCoral()
{
	color=8;
	gi->color = color;

	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchColorNavy()
{
	color=9;
	gi->color = color;
	
	player->SwitchBodyColor(color);
}

void UCharacterCustomizeWidget::SwitchAccessoryCanvas(int32 index)
{
	ws_AccessorySwitch->SetActiveWidgetIndex(index);
}

void UCharacterCustomizeWidget::OnClickedbtn_Hat()
{
	SwitchAccessoryCanvas(0);

}

void UCharacterCustomizeWidget::OnClickedbtn_Glass()
{
	SwitchAccessoryCanvas(1);
}

void UCharacterCustomizeWidget::OnClickedbtn_Tie()
{
	SwitchAccessoryCanvas(2);
}


void UCharacterCustomizeWidget::WearGlass0()
{
	face=0;
	gi->face=face;
	player->AttachGlass(face);
}

void UCharacterCustomizeWidget::WearGlass1()
{
	face=1;
	gi->face = face;
	player->AttachGlass(face);
}

void UCharacterCustomizeWidget::WearGlass2()
{
	face=2;
	gi->face = face;
	player->AttachGlass(face);
}

void UCharacterCustomizeWidget::WearGlass3()
{
	face=3;
	gi->face = face;
	player->AttachGlass(face);
}

void UCharacterCustomizeWidget::WearGlass4()
{
	face=4;
	gi->face = face;
	player->AttachGlass(face);
}

void UCharacterCustomizeWidget::WearGlass5()
{
	face=5;
	gi->face = face;
	player->AttachGlass(face);
}

void UCharacterCustomizeWidget::WearGlass6()
{
	face=6;
	gi->face = face;
	player->AttachGlass(face);
}


void UCharacterCustomizeWidget::WearHat1()
{
	hat = 0;
	gi->hat = hat;
	player->AttachHat(hat);
}

void UCharacterCustomizeWidget::WearHat2()
{
	hat = 1;
	gi->hat = hat;
	player->AttachHat(hat);
}


void UCharacterCustomizeWidget::WearTie1()
{
	tie = 0;
	gi->tie = tie;
	player->AttachTie(tie);
}

void UCharacterCustomizeWidget::WearTie2()
{
	tie = 1;
	gi->tie = tie;
	player->AttachTie(tie);
}

void UCharacterCustomizeWidget::WearTie3()
{
	tie = 2;
	gi->tie = tie;
	player->AttachTie(tie);
}
