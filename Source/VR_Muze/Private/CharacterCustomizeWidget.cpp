// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCustomizeWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/WidgetSwitcher.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstance.h"
#include "MyCharacter.h"

void UCharacterCustomizeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	APawn* Pawn = PlayerController->GetPawn();
	player = Cast<AMyCharacter>(Pawn);

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


}

void UCharacterCustomizeWidget::SwitchCanvas(int32 index)
{
	ws_CharacterCustomize->SetActiveWidgetIndex(index);
}

void UCharacterCustomizeWidget::OnClickedbtn_IntoBox()
{
	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	FName LevelName = "ViewLevel";

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void UCharacterCustomizeWidget::OnClickedbtn_IntoCustomize()
{
	SwitchCanvas(1);
}

void UCharacterCustomizeWidget::OnClickedbtn_CustomizeSave()
{
	//서버에 정보 보내기
}

void UCharacterCustomizeWidget::OnClickedbtn_BackSelect()
{
	SwitchCanvas(0);
}

void UCharacterCustomizeWidget::SwitchColorBlack()
{
	UMaterialInstance* BlackMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Game/DEV/KJS/Character/Character/Material/Body_Black.Body_Black")));

	player->GetMesh()->SetMaterial(0, BlackMaterial);
}

void UCharacterCustomizeWidget::SwitchColorWhite()
{

}

void UCharacterCustomizeWidget::SwitchColorSkyBlue()
{

}

void UCharacterCustomizeWidget::SwitchColorPink()
{
	UMaterialInstance* PinkMaterial = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Game/DEV/KJS/Character/Character/Material/Body_Pink.Body_Pink")));

	player->GetMesh()->SetMaterial(0, PinkMaterial);
}

void UCharacterCustomizeWidget::SwitchColorYellow()
{
}

void UCharacterCustomizeWidget::SwitchColorGreen()
{
}

void UCharacterCustomizeWidget::SwitchColorDeepYellow()
{
}

void UCharacterCustomizeWidget::SwitchColorViolet()
{

}

void UCharacterCustomizeWidget::SwitchColorCoral()
{
}

void UCharacterCustomizeWidget::SwitchColorNavy()
{
}
