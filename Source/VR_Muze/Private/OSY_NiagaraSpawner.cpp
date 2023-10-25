// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_NiagaraSpawner.h"
#include "OSY_GameInstance.h"
#include "LevelInfoTable.h"
#include "OSY_CSVParseLibrary.h"

// Sets default values
AOSY_NiagaraSpawner::AOSY_NiagaraSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//MyGameInstance = Cast<UOSY_GameInstance>(GetGameInstance());
	//if (MyGameInstance != nullptr)
	//{
	//	TArray<FString> spawnData = MyGameInstance->HttpRecieveData;
	//}

	
	PoolSize = 10;


}

// Called when the game starts or when spawned
void AOSY_NiagaraSpawner::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AOSY_NiagaraSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime+= DeltaTime;
}

void AOSY_NiagaraSpawner::spawnStart()
{
	// 버튼이 눌리면 시간이 초기화됨
	currentTime = 0;
	
	TArray<FLevelInfoTable> levelDataList;

	FString path = "D:\\Unreal\\XR-Unreal\\Content\\CSVData\\levelInfo.csv";

	UOSY_CSVParseLibrary::ReadMyCSV(path, levelDataList);

	if (levelDataList.Num() > 0)
	{
		FString resultText;
		for (FLevelInfoTable levelInfo : levelDataList)
		{


			UE_LOG(LogTemp, Warning, TEXT("Name : %s, spawnTime : %f, dieTime : %f, locationX : %f,locationY : %f, locationZ : %f, scale : %f, texture : %d"), *levelInfo.name, levelInfo.spawnTime, levelInfo.dieTime, levelInfo.locationX, levelInfo.locationY, levelInfo.locationZ, levelInfo.scale, levelInfo.texture);
		}
	}
	
}

