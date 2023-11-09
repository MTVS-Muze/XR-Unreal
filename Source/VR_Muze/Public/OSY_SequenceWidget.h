// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OSY_SequenceWidget.generated.h"

struct FActorSpawnInfo2
{
	FVector Location;
	FRotator Rotation;
	FVector Scale;
	UClass* ActorClass;
	float SpawnTime;
};
UCLASS()
class VR_MUZE_API UOSY_SequenceWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


#pragma region variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySequence)
	float CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySequence)
	float MaxTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySequence)
	float CorrespondingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySequence)
	float tempValue;
	
#pragma endregion

#pragma region UI
	/*UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UProgressBar* pb_TimeStaff;
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USlider* sl_TimeStaff;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* TimeTextBlock;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btn_Play;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btn_Stop;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btn_Pause;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btn_Save;

	

#pragma endregion

#pragma region Void
    UFUNCTION(BlueprintCallable)
    void UpdateProgressBar() const;
    UFUNCTION(BlueprintCallable)
	void HandleSliderValueChanged(float Value);
    UFUNCTION(BlueprintCallable)
 	void HandleSliderMouseCaptureBegin();
    UFUNCTION(BlueprintCallable)
	void HandleSliderMouseCaptureEnd();

	UFUNCTION()
	void SequencePlay();
	UFUNCTION()
	void SequencePause();
	UFUNCTION()
	void SequenceStop();
	UFUNCTION()
	void SequenceSave();
#pragma endregion

#pragma region Json


	UFUNCTION()
	void LoadJsonData();

	TArray<FVector> SavedLocations;
	TArray<FRotator> SavedRotations;
	TArray<FVector> SavedScales;
	TArray<float> SavedSpawnTimes;
	TArray<TSubclassOf<AActor>> SavedActorClasses;

	TArray<FActorSpawnInfo2> PendingSpawns;

	
	UPROPERTY()
	class AOSY_HttpRequestActor* HttpActor;
#pragma endregion

	

#pragma region Cast
	UPROPERTY(EditAnywhere,Category = MySettings)
	class UOSY_PropWidget* httpUI;
	
	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_TImeActor* TimeManager;
	UPROPERTY(EditAnywhere,Category = "MySettings")
	class AOSY_CreativeGameModeBase* gm;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
    UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere,Category = "MySettings")
	class USoundBase* superShy;

	
#pragma endregion 


};
