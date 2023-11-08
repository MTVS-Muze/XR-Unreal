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
	SelectedStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = SelectedStaticMesh;
	SelectedStaticMesh->SetRelativeScale3D(FVector(3.5f));

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	boxComp->SetupAttachment(SelectedStaticMesh);
	boxComp->SetRelativeScale3D(FVector(0.5,1,1));
	boxComp->SetRelativeLocation(FVector(0,-15,0));


}

// Called when the game starts or when spawned
void AKJS_BoxSofa::BeginPlay()
{
	Super::BeginPlay();
	
	UOSY_GameInstance* gi = Cast<UOSY_GameInstance>(GetGameInstance());
	if (gi)
	{
		//체크상태 확인
		ECheckBoxState SingleSit1State = gi->CheckboxStates.FindRef("Check_SingleSit1");
		ECheckBoxState SingleSit2State = gi->CheckboxStates.FindRef("Check_SingleSit2");
		ECheckBoxState DoubleSit1State = gi->CheckboxStates.FindRef("Check_DoubleSit1");
		ECheckBoxState DoubleSit2State = gi->CheckboxStates.FindRef("Check_DoubleSit2");
		//ECheckBoxState Sit1CheckState = gi->Sit1CheckState;
		
		//메쉬 설정
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

		else if (DoubleSit1State == ECheckBoxState::Checked)
		{
			if (StaticMeshOptions.IsValidIndex(2))
			{
				UStaticMesh* StaticMesh = StaticMeshOptions[2];
				SelectedStaticMesh->SetStaticMesh(StaticMesh);
			}
		}

		else if (DoubleSit2State == ECheckBoxState::Checked)
		{
			if (StaticMeshOptions.IsValidIndex(3))
			{
				UStaticMesh* StaticMesh = StaticMeshOptions[3];
				SelectedStaticMesh->SetStaticMesh(StaticMesh);
			}
		}

	}

}

// Called every frame
void AKJS_BoxSofa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKJS_BoxSofa::SetMesh()
{
	
}

