// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_MultiGameModeBase.h"
#include "OSY_GameInstance.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "OSY_HttpRequestActor.h"
#include "OSY_TImeActor.h"

AKJS_MultiGameModeBase::AKJS_MultiGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

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
    FTimerHandle TimerHandle;

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AKJS_MultiGameModeBase::Request, 0.5f, false);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AKJS_MultiGameModeBase::LoadJsonData, 3.0f, false);

    
}

void AKJS_MultiGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AKJS_MultiGameModeBase::StartLevelSequence, 5.0f, false);

    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            SeqActor->SequencePlayer->Play();
        }
    }

    HttpActor = Cast<AOSY_HttpRequestActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_HttpRequestActor::StaticClass()));

    TimeManager = Cast<AOSY_TImeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AOSY_TImeActor::StaticClass()));

    SendReq();
    Request();
}

void AKJS_MultiGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentTime = TimeManager->CurrentTime;

    if (TimeManager->bShouldTick)
    {
        Play();
    }
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


void AKJS_MultiGameModeBase::OnLevelSequenceFinished()
{
    FString MapName = GetWorld()->GetMapName();

	UWorld* World = GetWorld();
	if (World)
	{
		GetWorld()->ServerTravel("/Game/DEV/Map/Box_indoor_Multi?Listen");
	}
}

void AKJS_MultiGameModeBase::StartLevelSequence()
{
    ServerStartLevelSequence();
}

void AKJS_MultiGameModeBase::ServerStartLevelSequence_Implementation()
{
    MulticastStartLevelSequence();
}

void AKJS_MultiGameModeBase::MulticastStartLevelSequence_Implementation()
{

    for (TActorIterator<ALevelSequenceActor> It(GetWorld()); It; ++It)
    {
        ALevelSequenceActor* SeqActor = *It;
        if (SeqActor)
        {
            ULevelSequencePlayer* LevelSequencePlayer = SeqActor->GetSequencePlayer();

            FLevelSequenceCameraSettings CameraSettings;
            LevelSequencePlayer->Initialize(SeqActor->GetSequence(), GetWorld()->GetCurrentLevel(), CameraSettings);

            LevelSequencePlayer->Play();

            FString MapName = GetWorld()->GetMapName();

            if(MapName.Contains("PlanetariumSetup0"))
			{
				if (HasAuthority())
				{
					LevelSequencePlayer->OnFinished.AddDynamic(this, &AKJS_MultiGameModeBase::OnLevelSequenceFinished);
				}
			}
        }
    }
}

void AKJS_MultiGameModeBase::SendReq()
{
    if (HttpActor != nullptr)
    {
        HttpActor->SendRequest(gi->AllMap);

    }
}
void AKJS_MultiGameModeBase::Request()
{
    if (HttpActor != nullptr)
    {
        FString GiId = FString::FormatAsNumber(gi->PlayId);
        FString IdMapDetailInfo = gi->MapDetailInfo + "/" + GiId;
        HttpActor->SendRequest(IdMapDetailInfo);
    }
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

void AKJS_MultiGameModeBase::LoadJsonData()
{

    // gm에 있는 데이터를 PendingSpawns에 추가한다.
    UE_LOG(LogTemp, Warning, TEXT("PendingSpawns size: %d"), PendingSpawns.Num());

    for (int i = 0; i < Locations.Num(); i++)
    {
        FLevelInfo3 pendingSpawn;
        pendingSpawn.Location = Locations[i];
        pendingSpawn.Rotation = Rotations[i];
        pendingSpawn.Scale = Scales[i];


        FString BlueprintName = ActorClasses[i];
        BlueprintName = BlueprintName.Replace(TEXT("_C"), TEXT(""));
        FString BlueprintHame = ActorClasses[i];
        FString BlueprintPath = FString::Printf(TEXT("/Game/DEV/OOSY/Blueprints/BP_Niagara/%s.%s"), *BlueprintName, *BlueprintHame);


        UClass* ActorClass = LoadObject<UClass>(nullptr, *BlueprintPath);
        pendingSpawn.ActorClass = ActorClass;

        pendingSpawn.SpawnTime = SpawnTimes[i];
        pendingSpawn.LifeSpan = LifeSpans[i];

        PendingSpawns.Add(pendingSpawn);


    }

    TimeManager->bShouldTick = true;
    //Play();
}

void AKJS_MultiGameModeBase::Play()
{
    if (currentIndex >= PendingSpawns.Num())
    {
        return;
    }
    const FLevelInfo3& SpawnInfo = PendingSpawns[currentIndex];
    if (CurrentTime >= SpawnInfo.SpawnTime)
    {
        UWorld* World = GetWorld();
        if (World && SpawnInfo.ActorClass)
        {
            FActorSpawnParameters Params;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            AActor* SpawnedActor = World->SpawnActor<AActor>(SpawnInfo.ActorClass, SpawnInfo.Location, SpawnInfo.Rotation, Params);
            if (SpawnedActor)
            {
                SpawnedActor->SetActorScale3D(SpawnInfo.Scale);
                SpawnedActor->SetActorHiddenInGame(false);

                float DestroyTime = SpawnInfo.SpawnTime + SpawnedActor->GetLifeSpan();
                if (TimeManager->CurrentTime >= DestroyTime)
                {
                    SpawnedActor->Destroy();
                }
            }
        }

        // 다음 액터를 스폰하기 위해 currentNodeIndex를 증가시킵니다.
        currentIndex++;
    }
}

