// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OSY_PropWidget.generated.h"

struct FActorSpawnInfo
{
	FVector Location;
	FRotator Rotation;
	FVector Scale;
	UClass* ActorClass;
	float SpawnTime;
};
UCLASS()
class VR_MUZE_API UOSY_PropWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara1;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara2;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara3;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara4;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara5;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara6;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Save;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Exit;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_LoadJsonData;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_StartTick;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_StopTick;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_GetJson;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_PostJson;

	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara1;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara2;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara3;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara4;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara5;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara6;

	UPROPERTY()
	FString url ="http://192.168.0.232:8080/map/test/1";

	//UPROPERTY(VisibleAnywhere)
	//class AKJS_TestSpawnActor* Cube;


	UPROPERTY()
	class AOSY_HttpRequestActor* HttpActor;



public:
	FVector SavedLocation;
	FRotator SavedRotation;
	FVector SavedScale;
	
	float CurrentTime;

	UFUNCTION()
	void SpawnNiagara1();
	UFUNCTION()
	void SpawnNiagara2();
	UFUNCTION()
	void SpawnNiagara3();
	UFUNCTION()
	void SpawnNiagara4();
	UFUNCTION()
	void SpawnNiagara5();
	UFUNCTION()
	void SpawnNiagara6();
	

	UFUNCTION()
	void SaveJsonData();

	UFUNCTION()
	void LoadJsonData();

	UFUNCTION()
	void BackToMain();


	UFUNCTION()
	void ReadCSVSingle();

	UFUNCTION()
	void StartTick();

	UFUNCTION()
	void StopTick();

	UFUNCTION()
	void ReadCSVFile();

	UFUNCTION()
	void GetJSon();

	UFUNCTION()
	void PostJSon();

public:
	UPROPERTY(EditAnywhere,Category=MySettings)
	class UDataTable* levelInfoTable;

	UPROPERTY(EditAnywhere,Category=MySettings)
	class AOSY_NiagaraSpawner* factory;

public:
	//JSON

	TArray<FVector> SavedLocations;
	TArray<FRotator> SavedRotations;
	TArray<FVector> SavedScales;
	TArray<float> SavedSpawnTimes;
	TArray<TSubclassOf<AActor>> SavedActorClasses;

	TArray<FActorSpawnInfo> PendingSpawns;
	

	


	UPROPERTY(EditAnywhere,Category = "MySettings")
	class USoundBase* superShy;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;


};
