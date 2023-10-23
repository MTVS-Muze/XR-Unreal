// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PropWidget.h"
#include "Components/Button.h"
#include "KJS_TestSpawnActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UOSY_PropWidget::NativeConstruct()
{
	btn_BoxSpawn->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnBox);
	btn_Save->OnClicked.AddDynamic(this, &UOSY_PropWidget::SaveData);
	btn_Exit->OnClicked.AddDynamic(this, &UOSY_PropWidget::LevelTravel);


}

void UOSY_PropWidget::SpawnBox()
{
	FVector spawnLoc = FVector(0,0,0);
	FRotator spawnRot = FRotator(0,0,0);

	UWorld* World = GetWorld();
	if (World)
	{
		
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(proptest, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			// ������ �����ϸ� �߰����� ���� �� ������ ������ �� �ֽ��ϴ�.
			// ���� ���, ������ �����ϰų� �ٸ� �۾��� ������ �� �ֽ��ϴ�.
		}
		
	}
}

void UOSY_PropWidget::SaveData()
{

}

void UOSY_PropWidget::LevelTravel()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(),LevelName,true);
}
