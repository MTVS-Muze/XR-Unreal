// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OSY_GameInstance.generated.h"

 USTRUCT(BlueprintType)
struct FSessionSlotInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FString roomName = TEXT("");
	FString hostName = TEXT("");
	FString playerCount = TEXT("");
	int32 pingSpeed = 0;
	int32 sessionIndex = 0;
	
	FORCEINLINE void Set(FString rName, FString hName, FString pCount, int32 pSpeed, int32 index){ roomName = rName, hostName = hName, playerCount = pCount, pingSpeed = pSpeed, sessionIndex = index;}
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchSessionSignature, FSessionSlotInfo, sessionInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSearchFinishSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateSessionSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreateSessionCompletedSignature);

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

	UPROPERTY()
	FString playerName;

	UPROPERTY()
	FName currentSessionName;

	IOnlineSessionPtr sessionInterface;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;
	TSharedPtr<const FUniqueNetId> playerNetId;
	class FNamedOnlineSession* currentNamedSession;
	FSearchSessionSignature OnSearchInfoCompleted;
	FSearchFinishSignature OnSearchFinish;
	FUpdateSessionSignature OnUpdateOurSession;
	FOnCreateSessionCompletedSignature OnCreateSessionCompleted;


	void CreateMuzeSession(int32 playerCount, FName SessionName);

	void OnCreatedMuzeSession(FName sessionName, bool bWasSuccessful);

	//�����ڵ� ����
	FString GenerateRandomCode(int32 Length);

	void FindOtherSession();

	void OnFindOtherSession(bool bWasSuccessful);

	void JoinSelectedSession(FString RoomCode);

	void OnJoinFindSameSession(FName sessionName, EOnJoinSessionCompleteResult::Type result);

	UFUNCTION()
	void OnUpdateSession(FName sessionName, bool bIsUpdate);


   //üũ���� ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, ECheckBoxState> CheckboxStates;

	//VR ��ġ ���� Ȯ��
	//bool IsHMDConnected();
	UFUNCTION()
	void OnLevelLoaded(UWorld* LoadedWorld);

	FORCEINLINE FString GetInviteCode() { return invite_code; };

	//VR ��ġ �������

#pragma region SeYoung

	FString Token;

	UPROPERTY(EditAnywhere,Category = MySettings)
	TSubclassOf <class UOSY_LoginWidget>LoginWidget;
	
	
	class UOSY_LoginWidget* LoginUI;

#pragma endregion
private:
	bool bIsHMDConnectd;

	FString invite_code = "";
};
