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
#include "OSY_CreativeGameModeBase.h"
#include "OSY_GameInstance.h"
#include "OSY_OutLinerWidget.h"
#include "OSY_LightBaseActor.h"
#include "Runtime/UMG/Public/Components/WidgetSwitcher.h"




void UOSY_PropWidget::NativeConstruct()
{
	Super::NativeConstruct();

#pragma region Cast

	gm = GetWorld()->GetAuthGameMode<AOSY_CreativeGameModeBase>();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());
	if (gi != nullptr)
	{
		posturl = gi->Posturl;
		playergeturl = gi->Playergeturl;
		getlevelurl = gi->getlevelurl;
	}

	TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));
	HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));
#pragma endregion


#pragma region Sky
	btn_Directional->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnDirectional);
	btn_Point->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnPoint);
	btn_Spot->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnSpot);
	btn_HDRI1->OnClicked.AddDynamic(this, &UOSY_PropWidget::ChangeBackDrop);
	btn_HDRI2->OnClicked.AddDynamic(this, &UOSY_PropWidget::ChangeBackDrop2);
#pragma endregion
#pragma region Floor
	btn_Plane1->OnClicked.AddDynamic(this, &UOSY_PropWidget::ChangePlane);
	btn_Plane2->OnClicked.AddDynamic(this, &UOSY_PropWidget::ChangePlane2);
	
#pragma endregion
#pragma region Effect
	btn_Niagara1->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara1);
	btn_Niagara2->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara2);
	btn_Niagara3->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara3);
	btn_Niagara4->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara4);
	btn_Niagara5->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara5);
	btn_Niagara6->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara6);
	btn_meteorShower->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara7);
	btn_Snow->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara8);
	btn_Niagara9->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara9);
	btn_Niagara10->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnNiagara10);
	btn_Whale->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnMoon);
	btn_Moon->OnClicked.AddDynamic(this, &UOSY_PropWidget::SpawnWhale);
#pragma endregion
#pragma region Switch
	btn_Sky->OnClicked.AddDynamic(this, &UOSY_PropWidget::OnClickedbtn_Sky);
	btn_Floor->OnClicked.AddDynamic(this, &UOSY_PropWidget::OnClickedbtn_Floor);
	btn_Effect->OnClicked.AddDynamic(this, &UOSY_PropWidget::OnClickedbtn_Effect);

#pragma endregion

// back to main
	btn_Exit->OnClicked.AddDynamic(this, &UOSY_PropWidget::BackToMain);
// Local Save
	btn_Save->OnClicked.AddDynamic(this, &UOSY_PropWidget::SaveJsonData);
// sever get(????)
	btn_GetJson->OnClicked.AddDynamic(this, &UOSY_PropWidget::GetJSon);
// sever post
	btn_PostJson->OnClicked.AddDynamic(this, &UOSY_PropWidget::PostJSon);
// sever get(????)
	btn_GetLevel->OnClicked.AddDynamic(this, &UOSY_PropWidget::GetLevel);


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

		if (gm->OutLinerUI!= nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara1);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnNiagara2()
{
	FVector spawnLoc = FVector(240, -1110, 960);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara2, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara2);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
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

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara3);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
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

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara4);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
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

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara5);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
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

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara6);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnNiagara7()
{
	FVector spawnLoc = FVector(0, 0, 15000);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(MeteorShower, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(MeteorShower);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnNiagara8()
{
	FVector spawnLoc = FVector(0, 0, 3000);
	FRotator spawnRot = FRotator(0, 0, 0);


	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Snow, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}

		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Snow);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnNiagara9()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara9, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara9);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnNiagara10()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Niagara10, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Niagara10);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnMoon()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Moon, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Moon);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnWhale()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedProp = World->SpawnActor<AActor>(Whale, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			SavedLocations.Add(SpawnedProp->GetActorLocation());
			SavedRotations.Add(SpawnedProp->GetActorRotation());
			SavedScales.Add(SpawnedProp->GetActorScale3D());
			SavedActorClasses.Add(Whale);
			SavedSpawnTimes.Add(CurrentTime);
			SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::ChangeBackDrop()
{
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		AActor* FoundActor = *it;

		if (FoundActor->ActorHasTag(FName("HDRI")))
		{
			// 'HDRI' 태그를 가진 Actor를 찾았으므로, 여기에서 원하는 작업을 수행하세요.
			UE_LOG(LogTemp, Warning, TEXT("Found HDRI Actor: %s"), *FoundActor->GetName());

			if (FoundActor->ActorHasTag(FName("Evening")))
			{
				FoundActor->SetActorHiddenInGame(true);

			}
			else 
			{
				FoundActor->SetActorHiddenInGame(false);
			}
		}
	}

	
}

void UOSY_PropWidget::ChangeBackDrop2()
{
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		AActor* FoundActor = *it;

		if (FoundActor->ActorHasTag(FName("HDRI")))
		{
			// 'HDRI' 태그를 가진 Actor를 찾았으므로, 여기에서 원하는 작업을 수행하세요.
			UE_LOG(LogTemp, Warning, TEXT("Found HDRI Actor: %s"), *FoundActor->GetName());

			if (FoundActor->ActorHasTag(FName("Evening")))
			{
				FoundActor->SetActorHiddenInGame(false);

			}
			else if (FoundActor->ActorHasTag(FName("Snow")))
			{
				FoundActor->SetActorHiddenInGame(true);
			}
		}
	}

}

void UOSY_PropWidget::ChangePlane()
{
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		AActor* FoundActor = *it;

		if (FoundActor->ActorHasTag(FName("Plane")))
		{
			// 'HDRI' 태그를 가진 Actor를 찾았으므로, 여기에서 원하는 작업을 수행하세요.
			UE_LOG(LogTemp, Warning, TEXT("Found HDRI Actor: %s"), *FoundActor->GetName());

			if (FoundActor->ActorHasTag(FName("Water")))
			{
				FoundActor->SetActorHiddenInGame(true);

			}
			else
			{
				FoundActor->SetActorHiddenInGame(false);
			}
		}
	}
}

void UOSY_PropWidget::ChangePlane2()
{
	for (TActorIterator<AActor> it(GetWorld()); it; ++it)
	{
		AActor* FoundActor = *it;

		if (FoundActor->ActorHasTag(FName("Plane")))
		{
			// 'HDRI' 태그를 가진 Actor를 찾았으므로, 여기에서 원하는 작업을 수행하세요.
			UE_LOG(LogTemp, Warning, TEXT("Found HDRI Actor: %s"), *FoundActor->GetName());

			if (FoundActor->ActorHasTag(FName("Water")))
			{
				FoundActor->SetActorHiddenInGame(false);

			}
			else if (FoundActor->ActorHasTag(FName("Snow")))
			{
				FoundActor->SetActorHiddenInGame(true);
			}
		}
	}
}	

#pragma endregion 

void UOSY_PropWidget::SpawnDirectional()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOSY_LightBaseActor* SpawnedProp = World->SpawnActor<AOSY_LightBaseActor>(Directional, spawnLoc, spawnRot,param);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			//SavedLocations.Add(SpawnedProp->GetActorLocation());
			//SavedRotations.Add(SpawnedProp->GetActorRotation());
			//SavedScales.Add(SpawnedProp->GetActorScale3D());
			//SavedActorClasses.Add(Niagara1);
			//SavedSpawnTimes.Add(CurrentTime);
			//SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnPoint()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOSY_LightBaseActor* SpawnedProp = World->SpawnActor<AOSY_LightBaseActor>(Point, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			//SavedLocations.Add(SpawnedProp->GetActorLocation());
			//SavedRotations.Add(SpawnedProp->GetActorRotation());
			//SavedScales.Add(SpawnedProp->GetActorScale3D());
			//SavedActorClasses.Add(Niagara1);
			//SavedSpawnTimes.Add(CurrentTime);
			//SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::SpawnSpot()
{
	FVector spawnLoc = FVector(200, 0, 0);
	FRotator spawnRot = FRotator(0, 0, 0);

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AOSY_LightBaseActor* SpawnedProp = World->SpawnActor<AOSY_LightBaseActor>(Spot, spawnLoc, spawnRot);

		if (gm->OutLinerUI != nullptr)
		{
			gm->OutLinerUI->DisplayActorInfo();
		}


		if (SpawnedProp)
		{
			//SavedLocations.Add(SpawnedProp->GetActorLocation());
			//SavedRotations.Add(SpawnedProp->GetActorRotation());
			//SavedScales.Add(SpawnedProp->GetActorScale3D());
			//SavedActorClasses.Add(Niagara1);
			//SavedSpawnTimes.Add(CurrentTime);
			//SavedLifeSpans.Add(SpawnedProp->GetLifeSpan());
		}
	}
}

void UOSY_PropWidget::BackToMain()
{
	FName LevelName = "2_ViewLevel";

	UGameplayStatics::OpenLevel(GetWorld(),LevelName,true);
}

void UOSY_PropWidget::SaveJsonData()
{
	JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> LocationsArray;
	TArray<TSharedPtr<FJsonValue>> RotationsArray;
	TArray<TSharedPtr<FJsonValue>> ScalesArray;
	TArray<TSharedPtr<FJsonValue>> ActorClassesArray;
	TArray<TSharedPtr<FJsonValue>> SpawnTimeArray;
	TArray<TSharedPtr<FJsonValue>> LifeSpanArray;


	for (int i = 0; i < SavedLocations.Num(); i++)
	{
		TSharedPtr<FJsonObject> LocationObj = MakeShareable(new FJsonObject);
		LocationObj->SetNumberField(TEXT("X"), SavedLocations[i].X);
		LocationObj->SetNumberField(TEXT("Y"), SavedLocations[i].Y);
		LocationObj->SetNumberField(TEXT("Z"), SavedLocations[i].Z);
		LocationsArray.Add(MakeShareable(new FJsonValueObject(LocationObj)));

		TSharedPtr<FJsonObject> RotationObj = MakeShareable(new FJsonObject);
		RotationObj->SetNumberField(TEXT("Pitch"), SavedRotations[i].Pitch);
		RotationObj->SetNumberField(TEXT("Yaw"), SavedRotations[i].Yaw);
		RotationObj->SetNumberField(TEXT("Roll"), SavedRotations[i].Roll);
		RotationsArray.Add(MakeShareable(new FJsonValueObject(RotationObj)));

		TSharedPtr<FJsonObject> ScaleObj = MakeShareable(new FJsonObject);
		ScaleObj->SetNumberField(TEXT("X"), SavedScales[i].X);
		ScaleObj->SetNumberField(TEXT("Y"), SavedScales[i].Y);
		ScaleObj->SetNumberField(TEXT("Z"), SavedScales[i].Z);
		ScalesArray.Add(MakeShareable(new FJsonValueObject(ScaleObj)));

		ActorClassesArray.Add(MakeShareable(new FJsonValueString(SavedActorClasses[i]->GetName())));
		SpawnTimeArray.Add(MakeShareable(new FJsonValueNumber(SavedSpawnTimes[i])));
		LifeSpanArray.Add(MakeShareable(new FJsonValueNumber(SavedLifeSpans[i])));

	}

	JsonObject->SetArrayField(TEXT("Locations"), LocationsArray);
	JsonObject->SetArrayField(TEXT("Rotations"), RotationsArray);
	JsonObject->SetArrayField(TEXT("Scales"), ScalesArray);
	JsonObject->SetArrayField(TEXT("ActorClasses"), ActorClassesArray);
	JsonObject->SetArrayField(TEXT("SpawnTime"), SpawnTimeArray);
	JsonObject->SetArrayField(TEXT("LifeSpan"), LifeSpanArray);


	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	FString SavePath = FPaths::ProjectSavedDir() / TEXT("SavedData.json");
	FFileHelper::SaveStringToFile(JsonString, *SavePath);
	
}

#pragma region Json Get&Post

void UOSY_PropWidget::GetJSon()
{
	if (HttpActor != nullptr)
	{
		HttpActor->SendRequest(playergeturl);
	}
}

// 업로드 하는 함수
void UOSY_PropWidget::PostJSon()
{
	JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> LocationsArray;
	TArray<TSharedPtr<FJsonValue>> RotationsArray;
	TArray<TSharedPtr<FJsonValue>> ScalesArray;
	TArray<TSharedPtr<FJsonValue>> ActorClassesArray;
	TArray<TSharedPtr<FJsonValue>> SpawnTimeArray;
	TArray<TSharedPtr<FJsonValue>> LifeSpanArray;


	for (int i = 0; i < SavedLocations.Num(); i++)
	{
		TSharedPtr<FJsonObject> LocationObj = MakeShareable(new FJsonObject);
		LocationObj->SetNumberField(TEXT("X"), SavedLocations[i].X);
		LocationObj->SetNumberField(TEXT("Y"), SavedLocations[i].Y);
		LocationObj->SetNumberField(TEXT("Z"), SavedLocations[i].Z);
		LocationsArray.Add(MakeShareable(new FJsonValueObject(LocationObj)));

		TSharedPtr<FJsonObject> RotationObj = MakeShareable(new FJsonObject);
		RotationObj->SetNumberField(TEXT("Pitch"), SavedRotations[i].Pitch);
		RotationObj->SetNumberField(TEXT("Yaw"), SavedRotations[i].Yaw);
		RotationObj->SetNumberField(TEXT("Roll"), SavedRotations[i].Roll);
		RotationsArray.Add(MakeShareable(new FJsonValueObject(RotationObj)));

		TSharedPtr<FJsonObject> ScaleObj = MakeShareable(new FJsonObject);
		ScaleObj->SetNumberField(TEXT("X"), SavedScales[i].X);
		ScaleObj->SetNumberField(TEXT("Y"), SavedScales[i].Y);
		ScaleObj->SetNumberField(TEXT("Z"), SavedScales[i].Z);
		ScalesArray.Add(MakeShareable(new FJsonValueObject(ScaleObj)));

		ActorClassesArray.Add(MakeShareable(new FJsonValueString(SavedActorClasses[i]->GetName())));
		SpawnTimeArray.Add(MakeShareable(new FJsonValueNumber(SavedSpawnTimes[i])));
		LifeSpanArray.Add(MakeShareable(new FJsonValueNumber(SavedLifeSpans[i])));

	}

	JsonObject->SetArrayField(TEXT("Locations"), LocationsArray);
	JsonObject->SetArrayField(TEXT("Rotations"), RotationsArray);
	JsonObject->SetArrayField(TEXT("Scales"), ScalesArray);
	JsonObject->SetArrayField(TEXT("ActorClasses"), ActorClassesArray);
	JsonObject->SetArrayField(TEXT("SpawnTime"), SpawnTimeArray);
	JsonObject->SetArrayField(TEXT("LifeSpan"), LifeSpanArray);


	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	JsonStringPost = JsonString;
	
	if (HttpActor != nullptr)
	{
		HttpActor->PostRequest(gi->PostMyMap,JsonStringPost);
	}

	UE_LOG(LogTemp,Warning,TEXT("json : %s"),*JsonStringPost);
}




void UOSY_PropWidget::SwitchPropCanvas(int32 index)
{
	ws_PropSwitch->SetActiveWidgetIndex(index);
}

void UOSY_PropWidget::OnClickedbtn_Sky()
{
	SwitchPropCanvas(0);

}

void UOSY_PropWidget::OnClickedbtn_Floor()
{
	SwitchPropCanvas(1);

}

void UOSY_PropWidget::OnClickedbtn_Effect()
{
	SwitchPropCanvas(2);

}

// 레벨데이터를 받아내는 함수
void UOSY_PropWidget::GetLevel()
{
	if (HttpActor != nullptr)
	{
		HttpActor->SendRequest(playergeturl);
	}
}

#pragma endregion





