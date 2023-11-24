// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_MyInfoWidget.h"
#include "OSY_GameInstance.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_HttpRequestActor.h"
#include "KJS_CustomizeGameModeBase.h"

void UOSY_MyInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());

	KCgm = GetWorld()->GetAuthGameMode<AKJS_CustomizeGameModeBase>();
	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

	SetText();

	tb_Name->SetText(FText::FromString(gi->name));
	tb_email->SetText(FText::FromString(gi->email));

}

void UOSY_MyInfoWidget::SetText()
{
	if (HttpActor != nullptr)
	{
		HttpActor->GetImage(gi->profileImage);
	}
}
