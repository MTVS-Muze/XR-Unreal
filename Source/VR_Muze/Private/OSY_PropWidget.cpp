// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_PropWidget.h"
#include "Components/Button.h"
#include "KJS_TestSpawnActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "LevelInfoTable.h"
#include "OSY_CSVParseLibrary.h"
#include "OSY_HttpDownloader.h"
#include "OSY_HttpRequestActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "OSY_NiagaraSpawner.h"
#include "OSY_TImeActor.h"



void UOSY_PropWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	btn_Niagara1->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara1);
	btn_Niagara2->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara2);
	btn_Niagara3->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara3);
	btn_Niagara4->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara4);
	btn_Niagara5->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara5);
	btn_Niagara6->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara6);


	
	
	btn_GetJson->OnClicked.AddDynamic(this, &UOSY_PropWidget::GetJSon);
	btn_PostJson->OnClicked.AddDynamic(this, &UOSY_PropWidget::PostJSon);
	

	btn_Exit->OnClicked.AddDynamic(this, &UOSY_PropWidget::BackToMain);
	

	

	factory = Cast<AOSY_NiagaraSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_NiagaraSpawner::StaticClass()));

	TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));
	

}


void UOSY_PropWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (TimeManager->bShouldTick)
	{

		CurrentTime=TimeManager->CurrentTime;
	}
	



}

#pragma region Niagara
void UOSY_PropWidget::SpawnNiagara1()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara1, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara1);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SpawnNiagara2()
{
	FVector spawnLoc = FVector(200, -200, 0);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara2, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara2);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SpawnNiagara3()
{
	FVector spawnLoc = FVector(200, 200, 0);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara3, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara3);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SpawnNiagara4()
{
	FVector spawnLoc = FVector(100, 200, 0);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara4, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara4);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SpawnNiagara5()
{
	FVector spawnLoc = FVector(100, 100, 0);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara5, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara5);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}

void UOSY_PropWidget::SpawnNiagara6()
{
	FVector spawnLoc = FVector(100, 100, 0);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara6, spawnLoc, spawnRot);

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara6);
			SavedSpawnTimes.Add(HttpActor->currenTime);
		}
	}
}
#pragma endregion 




#pragma region Json Get&Post
void UOSY_PropWidget::GetJSon()
{
	if (HttpActor != nullptr)
	{
		HttpActor->SendRequest(url);

	}
}

void UOSY_PropWidget::PostJSon()
{
	if (HttpActor != nullptr)
	{
		HttpActor->PostRequest(url);

	}
	
}
#pragma endregion


void UOSY_PropWidget::BackToMain()
{
	FName LevelName = "2_LobbyMap";

	UGameplayStatics::OpenLevel(GetWorld(),LevelName,true);
}


// 특정라인의 데이터를 읽는 함수
void UOSY_PropWidget::ReadCSVSingle()
{
	if (levelInfoTable != nullptr)
	{
		
	}
}

void UOSY_PropWidget::ReadCSVFile()
{
	if (factory != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReadCSVFile Success"));
		factory->spawnStart();
	}

}






