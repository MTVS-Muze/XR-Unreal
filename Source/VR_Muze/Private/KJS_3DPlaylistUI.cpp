// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_3DPlaylistUI.h"
#include "Components/WidgetComponent.h"

// Sets default values
AKJS_3DPlaylistUI::AKJS_3DPlaylistUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Playlist = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI"));
}

// Called when the game starts or when spawned
void AKJS_3DPlaylistUI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKJS_3DPlaylistUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

