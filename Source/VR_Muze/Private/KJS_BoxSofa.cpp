// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_BoxSofa.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MediaLobbyWidget.h"
#include "OSY_GameInstance.h"

// Sets default values
AKJS_BoxSofa::AKJS_BoxSofa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = boxComp;

	SelectedStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SelectedStaticMesh->SetupAttachment(RootComponent);
	

	SelectedSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SelectedSkeletalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AKJS_BoxSofa::BeginPlay()
{
	Super::BeginPlay();
	
	UOSY_GameInstance* gi = Cast<UOSY_GameInstance>(GetGameInstance());
	if (gi)
	{
		ECheckBoxState SingleSit1State = gi->CheckboxStates.FindRef("Check_SingleSit1");
		ECheckBoxState SingleSit2State = gi->CheckboxStates.FindRef("Check_SingleSit2");
		//ECheckBoxState Sit1CheckState = gi->Sit1CheckState;
		
		if (SingleSit1State == ECheckBoxState::Checked)
		{
			if (StaticMeshOptions.IsValidIndex(0))
			{
				UStaticMesh* StaticMesh = StaticMeshOptions[0];
				SelectedStaticMesh->SetStaticMesh(StaticMesh);
			}
		}

		else if (SingleSit2State == ECheckBoxState::Checked)
		{
			if (StaticMeshOptions.IsValidIndex(1))
			{
				UStaticMesh* StaticMesh = StaticMeshOptions[1];
				SelectedStaticMesh->SetStaticMesh(StaticMesh);
			}
		}

	}

	//FString MeshPath1 = TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'");
	//UStaticMesh* LoadMesh1 = LoadStaticMesh(MeshPath1);
	//if (LoadMesh1)
	//{
	//	StaticMeshOptions.Add(LoadMesh1);
	//}
	//
	//FString MeshPath2 = TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'");
	//UStaticMesh* LoadMesh2 = LoadStaticMesh(MeshPath2);
	//if (LoadMesh2)
	//{
	//	StaticMeshOptions.Add(LoadMesh2);
	//}
}

// Called every frame
void AKJS_BoxSofa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKJS_BoxSofa::SetMesh()
{
	
}

