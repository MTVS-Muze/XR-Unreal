// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OSY_PropWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_PropWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_BoxSpawn;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Save;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Exit;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_CSVSingle;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_CSVAll;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_CSVFile;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_SendCSV;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_PostCSV;

	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> proptest;

	UPROPERTY()
	FString url ="http://192.168.0.10:8080/map/test";

	//UPROPERTY(VisibleAnywhere)
	//class AKJS_TestSpawnActor* Cube;


	UPROPERTY()
	class AOSY_HttpRequestActor* HttpActor;

public:
	UFUNCTION()
	void SpawnBox();

	UFUNCTION()
	void SaveData();

	UFUNCTION()
	void LevelTravel();

	UFUNCTION()
	void ReadCSVSingle();

	UFUNCTION()
	void ReadCSVAll();

	UFUNCTION()
	void ReadCSVFile();

	UFUNCTION()
	void SendCSV();

	UFUNCTION()
	void PostCSV();

public:
	UPROPERTY(EditAnywhere,Category=MySettings)
	class UDataTable* levelInfoTable;

	
};
