// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_GameInstance.h"
#include "OSY_PropWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "KJS_TypeInviteNumWidget.h"
#include "MyCharacter.h"



UOSY_GameInstance::UOSY_GameInstance()
{
	ConstructorHelpers::FClassFinder<UOSY_PropWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DEV/OOSY/Blueprints/BP_OSY_PropWidget.BP_OSY_PropWidget_C'"));

	if (TempWidget.Succeeded()) 
	{
		sideToolPanel = TempWidget.Class;
	}

	mySessionName = TEXT("Muze");

	bIsHMDConnectd = false;

	// Save data
	//UOSY_GameInstance* MyGameInstance = Cast<UOSY_GameInstance>(GetGameInstance());
	//if (MyGameInstance)
	//{
    //	MyGameInstance->HttpRecieveData = "YourDataHere";
	//}

	// Load data
	//UOSY_GameInstance* MyGameInstance = Cast<UOSY_GameInstance>(GetGameInstance());
	//if (MyGameInstance)
	//{
	//	FString LoadedData = HttpRecieveData->MyDataToStore;
    // LoadedData�� �����Ͱ� ����˴ϴ�.
	//}
}



void UOSY_GameInstance::OpenSideToolPanel()
{

	if (sideToolPanel != nullptr)
	{
		sideToolPanelInstance = CreateWidget<UOSY_PropWidget>(GetWorld(),sideToolPanel);

		if (sideToolPanelInstance != nullptr)
		{
			sideToolPanelInstance->AddToViewport();
		}
	}
}

void UOSY_GameInstance::CloseSideToolPanel()
{
	if (sideToolPanelInstance != nullptr)
	{
		sideToolPanelInstance->RemoveFromParent();
	}
	
}
/// <summary>
/// /////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
void UOSY_GameInstance::Init()
{
	Super::Init();

	//Online Session Interface API ���ٿ� �ν��Ͻ� ��������
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		sessionInterface = subsys->GetSessionInterface();

		//���� �̸� ���� �ڵ�� ����
		/*FString RoomCode = GenerateRandomCode(5);
		FName SessionName = FName(*RoomCode);

		CreateMuzeSession(4, SessionName);*/

		//���� �̺�Ʈ�� �Լ� ���ε� �ϱ�
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnCreatedMuzeSession);

		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnFindOtherSession);
	}

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UOSY_GameInstance::OnLevelLoaded);

}

void UOSY_GameInstance::CreateMuzeSession(int32 playerCount, FName SessionName)
{
	FOnlineSessionSettings settings;
	//LAN ��������, DEDICATED�������� ����
	settings.bIsDedicated = false;
	settings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");
	
	//�˻� ������ ������ �����Ѵ�.
	settings.bShouldAdvertise = true;

	//�ڱ� ������ ���޵� �� �ְ� �����Ѵ�.
	settings.bUsesPresence = true;

	//�ٸ� ������ �߰� ������ ����Ѵ�.
	settings.bAllowJoinInProgress = true;
	settings.bAllowJoinViaPresence = true;

	//���� ���� �ο��� �����Ѵ�.
	settings.NumPublicConnections = playerCount;

	//���� �߰����� �ֱ�
	settings.Set(FName("Room_Name"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("Host_Name"), mySessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//����
	bool isSuccess = sessionInterface->CreateSession(0, SessionName, settings);
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));

	if (isSuccess)
	{
		// ���� ������ �����ϸ�, ������ ������ �̸��� KJS_TypeInviteNumWidget�� ǥ��
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			AMyCharacter* muzeCharacter = Cast<AMyCharacter>(PlayerController->GetCharacter());
			if (muzeCharacter)
			{
				UKJS_TypeInviteNumWidget* InviteWidget = Cast<UKJS_TypeInviteNumWidget>(muzeCharacter->ShowHostCodeWidget);
				if (InviteWidget)
				{
					// ���� �ڵ带 �����ϰ�, �̸� InviteWidget�� ǥ���մϴ�.
					FString RoomCode = GenerateRandomCode(5);
					InviteWidget->CreateInviteCode(RoomCode);
				}
			}
		}
	}
}

void UOSY_GameInstance::OnCreatedMuzeSession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		bool result = GetWorld()->ServerTravel("/Game/DEV/Map/6_Box?Listen");
		UE_LOG(LogTemp, Warning, TEXT("Travel Result : %s"), result ? *FString("Success") : *FString("Failed"));

		//UKJS_TypeInviteNumWidget* InviteWidget = 
	}
}

FString UOSY_GameInstance::GenerateRandomCode(int32 Length)
{
	FString Code;
	FString Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	for (int32 i = 0; i < Length; i++)
	{
		int32 Index = FMath::RandRange(0, Characters.Len()-1);
		Code+=Characters[Index];
	}

	invite_code = Code;
	return Code;
}

void UOSY_GameInstance::FindOtherSession()
{
	sessionSearch = MakeShareable(new FOnlineSessionSearch());

	//���ǰ˻��� LAN���� �� ������ ���� ����
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	//���� ����(query) ����
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	//������ �˻����� ����
	sessionSearch->MaxSearchResults = 10;

	sessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
}

void UOSY_GameInstance::OnFindOtherSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;

		for (FOnlineSessionSearchResult result : searchResults)
		{
			FString roomName;
			result.Session.SessionSettings.Get(FName("Room_Name"), roomName);
			FString hostName;
			result.Session.SessionSettings.Get(FName("Room_Name"), hostName);
			int32 openNumber = result.Session.NumOpenPublicConnections;
			int32 maxNumber = result.Session.SessionSettings.NumPublicConnections;
			int32 pingSpeed = result.PingInMs;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session search failed"));
	}
}


void UOSY_GameInstance::OnLevelLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld->GetMapName() == "5_Box"|| LoadedWorld->GetMapName() == "6_Box")
	{
		UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
	}
}

