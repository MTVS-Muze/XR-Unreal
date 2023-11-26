// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OSY_PropWidget.generated.h"

struct FActorSpawnInfo
{
public:
	FVector Location;
	FRotator Rotation;
	FVector Scale;
	UClass* ActorClass;
	float SpawnTime;
	float LifeSpan;
	int text;

};

UCLASS()
class VR_MUZE_API UOSY_PropWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

#pragma region Sky

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_Directional;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_Point;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_Spot;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_HDRI1;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_HDRI2;

	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class AOSY_LightBaseActor> Directional;
	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class AOSY_LightBaseActor> Point;
	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class AOSY_LightBaseActor> Spot;

	UFUNCTION()
	void SpawnDirectional();
	UFUNCTION()
	void SpawnPoint();
	UFUNCTION()
	void SpawnSpot();
	UFUNCTION()
	void ChangeBackDrop();
	UFUNCTION()
	void ChangeBackDrop2();
#pragma endregion
#pragma region Floor

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Plane1;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Plane2;

	UFUNCTION()
	void ChangePlane();
	UFUNCTION()
	void ChangePlane2();
#pragma endregion

#pragma region Effect
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
	class UButton* btn_meteorShower;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Snow;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Moon;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Whale;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara9;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Niagara10;
	


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
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> MeteorShower;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Snow;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara9;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Niagara10;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Moon;
	UPROPERTY(EditAnywhere, Category= MySettings)
	TSubclassOf<class AActor> Whale;

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
	void SpawnNiagara7();
	UFUNCTION()
	void SpawnNiagara8();
	UFUNCTION()
	void SpawnNiagara9();
	UFUNCTION()
	void SpawnNiagara10();
	UFUNCTION()
	void SpawnMoon();
	UFUNCTION()
	void SpawnWhale();
#pragma endregion 

#pragma region Switch
	UPROPERTY()
	class UOSY_OutLinerWidget* OutlinerWidgetInstance;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = AccessoryMain)
	class UWidgetSwitcher* ws_PropSwitch;

	UFUNCTION()
	void SwitchPropCanvas(int32 index);

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = AccessoryMain)
	class UButton* btn_Sky;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = AccessoryMain)
	class UButton* btn_Floor;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = AccessoryMain)
	class UButton* btn_Effect;

	UFUNCTION()
	void OnClickedbtn_Sky();

	UFUNCTION()
	void OnClickedbtn_Floor();

	UFUNCTION()
	void OnClickedbtn_Effect();

#pragma endregion 


#pragma region Else
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Save;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_Exit;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_LoadJsonData;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_GetLevel;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = Button)
	class UButton* btn_GetJson;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=Button)
	class UButton* btn_PostJson;



	UPROPERTY()
	FString posturl;
	UPROPERTY()
	FString playergeturl;
	UPROPERTY()
	FString getlevelurl;



	UPROPERTY(EditAnywhere, Category= MySettings)
	class AOSY_HttpRequestActor* HttpActor;

	TSharedPtr<FJsonObject> JsonObject;

	FString JsonString;

public:
	FVector SavedLocation;
	FRotator SavedRotation;
	FVector SavedScale;
	
	float CurrentTime;

#pragma region Niagara


#pragma endregion


	UFUNCTION()
	void BackToMain();

	UFUNCTION()
	void SaveJsonData();

	UFUNCTION()
	void GetLevel();

	UFUNCTION()
	void GetJSon();

	UFUNCTION()
	void PostJSon();

public:
	UPROPERTY(EditAnywhere,Category=MySettings)
	class UDataTable* levelInfoTable;

	

public:
	//JSON

	TArray<FVector> SavedLocations;
	TArray<FRotator> SavedRotations;
	TArray<FVector> SavedScales;
	TArray<float> SavedSpawnTimes;
	TArray<float> SavedLifeSpans;
	TArray<TSubclassOf<AActor>> SavedActorClasses;
	TArray<int> Texts;

	TArray<FActorSpawnInfo> PendingSpawns;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class USoundBase* superShy;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_CreativeGameModeBase* gm;

	UPROPERTY()
	class UOSY_GameInstance* gi;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	FString JsonStringPost;

	
};
