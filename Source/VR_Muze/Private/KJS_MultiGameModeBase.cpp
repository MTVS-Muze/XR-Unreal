// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_MultiGameModeBase.h"
#include "OSY_GameInstance.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"



void AKJS_MultiGameModeBase::BeginPlay()
{
    gi = Cast<UOSY_GameInstance>(GetGameInstance());

    if (gi)
    {
        ECheckBoxState DoubleSit1State = gi->CheckboxStates.FindRef("Check_DoubleSit1");
        ECheckBoxState DoubleSit2State = gi->CheckboxStates.FindRef("Check_DoubleSit2");

        if (DoubleSit1State == ECheckBoxState::Checked)
        {
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(-142.0, 16.8, 92)));
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(156.0, 16.8, 92)));
        }
        else if (DoubleSit2State == ECheckBoxState::Checked)
        {
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(-84.0, 50.0, 92)));
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(72.0, 23.0, 92)));
        }
    }

    APlayerController* HostController = GetWorld()->GetFirstPlayerController();
    if (HostController)
    {
        APlayerStart* HostStartSpot = UsedPlayerStarts[0];
        UsedPlayerStarts.RemoveAt(0);
        HostController->GetPawn()->SetActorLocation(HostStartSpot->GetActorLocation());
    }
}

APlayerStart* AKJS_MultiGameModeBase::SpawnPlayerStart(FVector Location)
{
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    return GetWorld()->SpawnActor<APlayerStart>(Location, FRotator(0,90,0), Params);
	//APlayerStart* SpawnedActor = GetWorld()->SpawnActor<APlayerStart>(Location, FRotator(0, 90, 0), Params);
    //
	//if (SpawnedActor)
	//{
	//	FVector SpawnedLocation = SpawnedActor->GetActorLocation();
	//	UE_LOG(LogTemp, Warning, TEXT("PlayerStart spawned at: %s"), *SpawnedLocation.ToString());
	//}
    //
	//return SpawnedActor;
}

AActor* AKJS_MultiGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    if (UsedPlayerStarts.Num() > 0)
    {
        APlayerStart* StartSpot = UsedPlayerStarts[0];
        UsedPlayerStarts.RemoveAt(0);
        return StartSpot;
    }

    return Super::ChoosePlayerStart_Implementation(Player);
}

