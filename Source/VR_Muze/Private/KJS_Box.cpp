// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_Box.h"
#include "Components/BoxComponent.h"

// Sets default values
AKJS_Box::AKJS_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxOutside = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxOutside"));
	RootComponent=BoxOutside;
	ConstructorHelpers::FObjectFinder<UStaticMesh>OutsideMesh(TEXT("/Script/Engine.StaticMesh'/Game/Sojin/indoor_Object001.indoor_Object001'"));
	if (OutsideMesh.Succeeded())
	{
		BoxOutside->SetStaticMesh(OutsideMesh.Object);
	}
	BoxOutside->SetRelativeScale3D(FVector(30.f));

	BoxInside = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxInside"));
	BoxInside->SetupAttachment(BoxOutside);
	ConstructorHelpers::FObjectFinder<UStaticMesh>InsideMesh(TEXT("/Script/Engine.StaticMesh'/Game/Sojin/indoor_Rectangle001.indoor_Rectangle001'"));
	if (InsideMesh.Succeeded())
	{
		BoxInside->SetStaticMesh(InsideMesh.Object);
	}
	BoxInside->SetRelativeLocation(FVector(0, 0, 30));
	BoxInside->SetRelativeScale3D(FVector(0.9f));




}

// Called when the game starts or when spawned
void AKJS_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKJS_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

