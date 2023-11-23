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

void UCharacterCustomizeWidget::SwitchBodyColor(int32 Index)
{
	if (Index >= 0 && Index < BodyMaterials.Num() && BodyMaterials[Index] != nullptr)
	{
		player->GetMesh()->SetMaterial(0, BodyMaterials[Index]);
	}
}

void UCharacterCustomizeWidget::SwitchColorBlack()
{
	SwitchBodyColor(0);
	
	color=0;
	gi->color=color;

}

void UCharacterCustomizeWidget::SwitchColorWhite()
{
	SwitchBodyColor(1);
	color=1;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorSkyBlue()
{
	SwitchBodyColor(2);
	color=2;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorPink()
{
	//UMaterialInstance* PinkMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Game/DEV/KJS/Character/Character/Material/Body_Pink.Body_Pink")));

	SwitchBodyColor(3);
	color=3;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorYellow()
{
	SwitchBodyColor(4);
	color=4;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorGreen()
{
	SwitchBodyColor(5);
	color=5;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorDeepYellow()
{
	SwitchBodyColor(6);
	color=6;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorViolet()
{
	SwitchBodyColor(7);
	color=7;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorCoral()
{
	SwitchBodyColor(8);
	color=8;
	gi->color = color;
}

void UCharacterCustomizeWidget::SwitchColorNavy()
{
	SwitchBodyColor(9);
	color=9;
	gi->color = color;
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

void UCharacterCustomizeWidget::AttachGlass(int32 Index)
{
	if (Index >= 0 && Index < GlassMeshes.Num() && GlassMeshes[Index] != nullptr)
	{
		if (AttachedGlass)
		{
			AttachedGlass->DestroyComponent();
			AttachedGlass = nullptr;
		}
		AttachedGlass = NewObject<UStaticMeshComponent>(player);
		AttachedGlass->SetStaticMesh(GlassMeshes[Index]);
		AttachedGlass->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GlassSocket"));
		AttachedGlass->RegisterComponent();
	}
}

void UCharacterCustomizeWidget::WearGlass0()
{
	AttachGlass(0);
	face=0;
	gi->face=face;
}

void UCharacterCustomizeWidget::WearGlass1()
{
	AttachGlass(1);
	face=1;
	gi->face = face;
}

void UCharacterCustomizeWidget::WearGlass2()
{
	AttachGlass(2);
	face=2;
	gi->face = face;
}

void UCharacterCustomizeWidget::WearGlass3()
{
	AttachGlass(3);
	face=3;
	gi->face = face;
}

void UCharacterCustomizeWidget::WearGlass4()
{
	AttachGlass(4);
	face=4;
	gi->face = face;
}

void UCharacterCustomizeWidget::WearGlass5()
{
	AttachGlass(5);
	face=5;
	gi->face = face;
}

void UCharacterCustomizeWidget::WearGlass6()
{
	AttachGlass(6);
	face=6;
	gi->face = face;
}


void UCharacterCustomizeWidget::AttachHat(int32 Index)
{
	if (Index >= 0 && Index < HatMeshes.Num() && HatMeshes[Index] != nullptr)
	{
		if (AttachedHat)
		{
			AttachedHat->DestroyComponent();
			AttachedHat = nullptr;
		}
		AttachedHat = NewObject<UStaticMeshComponent>(player);
		AttachedHat->SetStaticMesh(HatMeshes[Index]);
		AttachedHat->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HatSocket"));
		AttachedHat->RegisterComponent();
	}
}


void UCharacterCustomizeWidget::WearHat1()
{
	AttachHat(0);
	hat = 0;
	gi->hat = hat;
}

void UCharacterCustomizeWidget::WearHat2()
{
	AttachHat(1);
	hat = 1;
	gi->hat = hat;
}

void UCharacterCustomizeWidget::AttachTie(int32 Index)
{
	if (Index >= 0 && Index < TieMeshes.Num() && TieMeshes[Index] != nullptr)
	{
		if (AttachedTie)
		{
			AttachedTie->DestroyComponent();
			AttachedTie = nullptr;
		}
		AttachedTie = NewObject<UStaticMeshComponent>(player);
		AttachedTie->SetStaticMesh(TieMeshes[Index]);
		AttachedTie->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("TieSocket"));
		AttachedTie->RegisterComponent();
	}
}

void UCharacterCustomizeWidget::WearTie1()
{
	AttachTie(0);
	tie = 0;
	gi->tie = tie;
}

void UCharacterCustomizeWidget::WearTie2()
{
	AttachTie(1);
	tie = 1;
	gi->tie = tie;
}

void UCharacterCustomizeWidget::WearTie3()
{
	AttachTie(2);
	tie = 2;
	gi->tie = tie;
}
