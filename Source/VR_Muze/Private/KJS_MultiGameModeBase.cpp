// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_MultiGameModeBase.h"
#include "OSY_GameInstance.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"

void AKJS_MultiGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    gi = Cast<UOSY_GameInstance>(GetGameInstance());

    if (gi)
    {
        ECheckBoxState DoubleSit1State = gi->CheckboxStates.FindRef("Check_DoubleSit1");
        ECheckBoxState DoubleSit2State = gi->CheckboxStates.FindRef("Check_DoubleSit2");

        if (DoubleSit1State == ECheckBoxState::Checked)
        {
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(-142.0, 16.8, 92), FRotator(0, 90, 0), "First"));
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(156.0, 16.8, 92), FRotator(0, 90, 0) , "Second"));
        }
        else if (DoubleSit2State == ECheckBoxState::Checked)
        {
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(-84.0, 50.0, 92), FRotator(0, 90, 0) , "First"));
            UsedPlayerStarts.Add(SpawnPlayerStart(FVector(72.0, 23.0, 92), FRotator(0, 90, 0), "Second"));
        }
    }
}

void AKJS_MultiGameModeBase::BeginPlay()
{
	
}

APlayerStart* AKJS_MultiGameModeBase::SpawnPlayerStart(FVector Location, FRotator Rotation , FString Tag)
{
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	APlayerStart* SpawnedActor = GetWorld()->SpawnActor<APlayerStart>(Location, Rotation, Params);
	if (SpawnedActor)
	{
        // 태그를 추가합니다.
        SpawnedActor->Tags.AddUnique(FName(*Tag));

        FVector SpawnedLocation = SpawnedActor->GetActorLocation();
        FRotator SpawnedRotation = SpawnedActor->GetActorRotation();
        UE_LOG(LogTemp, Warning, TEXT("PlayerStart (%s) spawned at: %s"), *Tag, *SpawnedLocation.ToString());
        UE_LOG(LogTemp, Warning, TEXT("PlayerStart (%s) Rotate: %s"), *Tag, *SpawnedRotation.ToString());
	}
    
	return SpawnedActor;
}


AActor* AKJS_MultiGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    TArray<APlayerStart*> playerStarts;
    playerStarts.SetNum(2);

    for (TActorIterator<APlayerStart> it(GetWorld()); it; ++it)
    {
        APlayerStart* ps = *it;

        if (ps->ActorHasTag(FName("First")))
        {
            playerStarts[0] = ps;
        }
        else
        {
            playerStarts[1] = ps;
        }
    }

    APlayerStart* chooseStart = playerStarts[callNumber];
    callNumber = (callNumber+1)% playerStarts.Num();
    return chooseStart;
}

