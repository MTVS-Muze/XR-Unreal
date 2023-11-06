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
	/// <param name="n">���̾ư����̸�</param>
	/// <param name="s">�����ð�</param>
	/// <param name="d">�״½ð�</param>
	/// <param name="lx">X��ǥ</param>
	/// <param name="ly">Y��ǥ</param>
	/// <param name="lz">Z��ǥ</param>
	/// <param name="sc">������</param>
	/// <param name="t">�����ؽ����ε���</param>
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

public:	// ����
	// widget source
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UOSY_PropWidget> sideToolPanel;

	UPROPERTY()
	class UOSY_PropWidget* sideToolPanelInstance;

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
	//��Ʈ��ũ
	UPROPERTY()
	FString mySessionName;

	IOnlineSessionPtr sessionInterface;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	void CreateMuzeSession(int32 playerCount, FName SessionName);

	void OnCreatedMuzeSession(FName sessionName, bool bWasSuccessful);

	//�����ڵ� ����
	FString GenerateRandomCode(int32 Length);

	void FindOtherSession();

	void OnFindOtherSession(bool bWasSuccessful);

	//bool GetSearchResultByName(FName SessionName, FOnlineSessionSearchResult& SearchResult);

	//void JoinSession(FOnlineSessionSearchResult SearchResult);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
   //ECheckBoxState Sit1CheckState;

   //üũ���� ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, ECheckBoxState> CheckboxStates;

	//VR ��ġ ���� Ȯ��
	//bool IsHMDConnected();
	UFUNCTION()
	void OnLevelLoaded(UWorld* LoadedWorld);
	//VR ��ġ �������

	FORCEINLINE FString GetInviteCode() { return invite_code; };

private:
	bool bIsHMDConnectd;

	FString invite_code = "";
};
