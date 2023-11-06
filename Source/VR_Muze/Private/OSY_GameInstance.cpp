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
    // LoadedData에 데이터가 저장됩니다.
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

	//Online Session Interface API 접근용 인스턴스 가져오기
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		sessionInterface = subsys->GetSessionInterface();

		//세션 이름 랜덤 코드로 생성
		/*FString RoomCode = GenerateRandomCode(5);
		FName SessionName = FName(*RoomCode);

		CreateMuzeSession(4, SessionName);*/

		//세션 이벤트에 함수 바인딩 하기
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnCreatedMuzeSession);

		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnFindOtherSession);
	}

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UOSY_GameInstance::OnLevelLoaded);

}

void UOSY_GameInstance::CreateMuzeSession(int32 playerCount, FName SessionName)
{
	FOnlineSessionSettings settings;
	//LAN 연결인지, DEDICATED연결인지 설정
	settings.bIsDedicated = false;
	settings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");
	
	//검색 가능한 방으로 설정한다.
	settings.bShouldAdvertise = true;

	//자기 정보를 전달될 수 있게 설정한다.
	settings.bUsesPresence = true;

	//다른 유저의 중간 입장을 허용한다.
	settings.bAllowJoinInProgress = true;
	settings.bAllowJoinViaPresence = true;

	//입장 가능 인원을 설정한다.
	settings.NumPublicConnections = playerCount;

	//세션 추가설정 넣기
	settings.Set(FName("Room_Name"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("Host_Name"), mySessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//세션
	bool isSuccess = sessionInterface->CreateSession(0, SessionName, settings);
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));

	if (isSuccess)
	{
		// 세션 생성에 성공하면, 생성된 세션의 이름을 KJS_TypeInviteNumWidget에 표시
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			AMyCharacter* muzeCharacter = Cast<AMyCharacter>(PlayerController->GetCharacter());
			if (muzeCharacter)
			{
				UKJS_TypeInviteNumWidget* InviteWidget = Cast<UKJS_TypeInviteNumWidget>(muzeCharacter->ShowHostCodeWidget);
				if (InviteWidget)
				{
					// 랜덤 코드를 생성하고, 이를 InviteWidget에 표시합니다.
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

	//세션검색을 LAN으로 할 것인지 여부 설정
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	//세션 쿼리(query) 설정
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	//세션의 검색량을 설정
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

