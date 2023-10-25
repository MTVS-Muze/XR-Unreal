// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OSY_GameInstance.generated.h"


USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DieTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LocationX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LocationY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LocationZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Texture;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="n">나이아가라이름</param>
	/// <param name="s">생성시간</param>
	/// <param name="d">죽는시간</param>
	/// <param name="lx">X좌표</param>
	/// <param name="ly">Y좌표</param>
	/// <param name="lz">Z좌표</param>
	/// <param name="sc">스케일</param>
	/// <param name="t">적용텍스쳐인덱스</param>
	FORCEINLINE void Set(FString n, float s, float d, float lx, float ly, float lz, float sc, int t)
	{
		Name = n; SpawnTime = s, DieTime = d, LocationX = lx, LocationY = ly, LocationZ = lz, Scale = sc, Texture = t;
	};


};

/**
 * 
 */
UCLASS()
class VR_MUZE_API UOSY_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UOSY_GameInstance();

public:
	virtual void Init() override;

public:	// 세영
	// widget source
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UOSY_PropWidget> sideToolPanel;

	UPROPERTY()
	UOSY_PropWidget* sideToolPanelInstance;

	// Function
	UFUNCTION(BlueprintCallable)
	void OpenSideToolPanel();

	UFUNCTION(BlueprintCallable)
	void CloseSideToolPanel();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> HttpRecieveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSpawnData InsMyData;
	
public:
	//네트워크
	UPROPERTY()
	FString mySessionName;

	IOnlineSessionPtr sessionInterface;

	void CreateMuzeSession();

	void OnCreatedMuzeSession(FName sessionName, bool bWasSuccessful);

};
