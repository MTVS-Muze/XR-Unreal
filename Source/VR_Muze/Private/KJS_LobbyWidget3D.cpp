// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_LobbyWidget3D.h"
#include "Components/WidgetComponent.h"

// Sets default values
AKJS_LobbyWidget3D::AKJS_LobbyWidget3D()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Lobby = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));

}

// Called when the game starts or when spawned
void AKJS_LobbyWidget3D::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKJS_LobbyWidget3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

