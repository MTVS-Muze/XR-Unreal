// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_GameInstance.h"
#include "OSY_PropWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "KJS_TypeInviteNumWidget.h"
#include "MyCharacter.h"
#include "OSY_LoginWidget.h"
#include "Net/UnrealNetwork.h"



UOSY_GameInstance::UOSY_GameInstance()
{
	ConstructorHelpers::FClassFinder<UOSY_PropWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/DEV/OOSY/Blueprints/BP_OSY_PropWidget.BP_OSY_PropWidget_C'"));

	if (TempWidget.Succeeded()) 
	{
		sideToolPanel = TempWidget.Class;
	}

	mySessionName = TEXT("Muze");

	bIsHMDConnectd = false;

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

		//세션 이벤트에 함수 바인딩 하기
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnCreatedMuzeSession);
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnFindOtherSession);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnJoinFindSameSession);
	}

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UOSY_GameInstance::OnLevelLoaded);
#pragma region Seyoung

	


#pragma endregion

}

void UOSY_GameInstance::CreateMuzeSession(int32 playerCount)
{
	FName SessionName = mySessionName;
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
	settings.NumPublicConnections = 4;

	settings.Set(FName("Room_Name"), SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	settings.Set(FName("Host_Name"), mySessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//세션
	bool isSuccess = sessionInterface->CreateSession(0, SessionName, settings);
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));

	if (isSuccess)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		//if (PlayerController)
		//{
		//	AMyCharacter* muzeCharacter = Cast<AMyCharacter>(PlayerController->GetCharacter());
		//	if (muzeCharacter)
		//	{
		//		// 세션 생성에 성공하면, 생성된 세션의 이름을 KJS_TypeInviteNumWidget에 표시
		//		//UKJS_TypeInviteNumWidget* InviteWidget = Cast<UKJS_TypeInviteNumWidget>(muzeCharacter->ShowHostCodeWidget);
		//		//if (InviteWidget)
		//		//{
		//		//	// 랜덤 코드를 생성하고, 이를 InviteWidget에 표시합니다.
		//		//	FString RoomCode = GenerateRandomCode(5);
		//		//	InviteWidget->CreateInviteCode(RoomCode);
		//		//	
		//		//}
		//
		//
		//	}
		//}
	}
}

void UOSY_GameInstance::OnCreatedMuzeSession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		bool result = GetWorld()->ServerTravel("/Game/DEV/Map/Box_indoor_Multi?Listen");
		OnCreateSessionCompleted.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Travel Result : %s"), result ? *FString("Success") : *FString("Failed"));
	}
}

//FString UOSY_GameInstance::GenerateRandomCode(int32 Length)
//{
//	FString Code;
//	FString Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//
//	for (int32 i = 0; i < Length; i++)
//	{
//		int32 Index = FMath::RandRange(0, Characters.Len()-1);
//		Code+=Characters[Index];
//	}
//
//	invite_code = Code;
//	return Code;
//}

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

		for (FOnlineSessionSearchResult& result : searchResults)
		{
			FString roomName;
			result.Session.SessionSettings.Get(FName("Room_Name"), roomName);

			if (roomName == mySessionName)
			{
				// 세션 참가 코드 추가
				JoinMuzeSession(result);
				break;
			}
		}

		//for (int i = 0; i < searchResults.Num(); i++)
		//{
		//	FOnlineSessionSearchResult result = searchResults[i];
		//	FString roomName;
		//	result.Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
		//	//if (!roomName.Contains("Muze_Room")) continue;
		//	FString hostName;
		//	result.Session.SessionSettings.Get(FName("HOST_NAME"), hostName);
		//	int32 openNumber = result.Session.NumOpenPublicConnections;
		//	int32 maxNumber = result.Session.SessionSettings.NumPublicConnections;
		//	int32 pingSpeed = result.PingInMs;
		//
		//	UE_LOG(LogTemp, Warning, TEXT("RoomName : %s, HostName : %s, Number : %d/%d, PingSpeed : %d"), *roomName, *hostName, openNumber, //maxNumber, pingSpeed);
		//
		//	FSessionSlotInfo slotInfo;
		//	slotInfo.Set(roomName, hostName, FString::Printf(TEXT("%d/%d"), openNumber, maxNumber), pingSpeed, i);
		//
		//	//JoinMuzeSession();
		//	OnSearchInfoCompleted.Broadcast(slotInfo);
		//}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session search failed"));
	}
}


//void UOSY_GameInstance::JoinSelectedSession(FString RoomCode)
//{
//	if (sessionSearch.IsValid())
//	{
//		for (int i = 0; i < sessionSearch->SearchResults.Num(); i++)
//		{
//			FString sessionName;
//			sessionSearch->SearchResults[i].Session.SessionSettings.Get(FName("Room_Name"), sessionName);
//			if (sessionName == RoomCode)
//			{
//				sessionInterface->JoinSession(0, FName(sessionName), sessionSearch->SearchResults[i]);
//				break;
//			}
//		}
//	}
//}

void UOSY_GameInstance::JoinMuzeSession(FOnlineSessionSearchResult SearchResult)
{
	FName SessionName = mySessionName;

	if (sessionInterface.IsValid() && SearchResult.IsValid())
	{
		
		sessionInterface->JoinSession(0, SessionName, SearchResult);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to join session."));
	}
}

void UOSY_GameInstance::OnJoinFindSameSession(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), result == EOnJoinSessionCompleteResult::Success ? *FString(TEXT("Success")) : *FString(TEXT("Failed")));

	switch (result)
	{
	case EOnJoinSessionCompleteResult::Success:
	{
		UE_LOG(LogTemp, Warning, TEXT("Successed : %s"), *sessionName.ToString());
		currentSessionName = sessionName;
		currentNamedSession = sessionInterface->GetNamedSession(currentSessionName);
		APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
		if (playerCon != nullptr)
		{
			FString url;
			sessionInterface->GetResolvedConnectString(sessionName, url);
			if (!url.IsEmpty())
			{
				UE_LOG(LogTemp, Warning, TEXT("Connection URL : %s"), *url);
				playerCon->ClientTravel(url, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		UE_LOG(LogTemp, Warning, TEXT("Session Is Full"));
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		UE_LOG(LogTemp, Warning, TEXT("%s"), "Session Does Not Exist");
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		UE_LOG(LogTemp, Warning, TEXT("%s"), "Could Not RetrieveAddress");
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		UE_LOG(LogTemp, Warning, TEXT("%s"), "Already In Session");
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		UE_LOG(LogTemp, Warning, TEXT("%s"), "UnknownError");
		break;
	default:
		break;
	}
}

void UOSY_GameInstance::OnUpdateSession(FName sessionName, bool bIsUpdate)
{
	if (sessionName == currentSessionName)
	{
		OnUpdateOurSession.Broadcast();
	}
}


void UOSY_GameInstance::OnLevelLoaded(UWorld* LoadedWorld)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s(%d) map name: %s"), *FString(__FUNCTION__), __LINE__, *LoadedWorld->GetMapName());

	if (LoadedWorld->GetMapName() == "Box_indoor_Single"|| LoadedWorld->GetMapName() == "Box_indoor_Multi" || LoadedWorld->GetMapName() == "StreetCar_Play")
	{
		UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
	}

	if (LoadedWorld->GetMapName().Contains("Box_indoor_Multi"))
	{
		UWorld* World = GetWorld();

		if(World)
		{
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FRotator SofaRotation = FRotator::ZeroRotator; // 회전값 0
			ECheckBoxState DoubleSit1State = CheckboxStates.FindRef("Check_DoubleSit1");
			ECheckBoxState DoubleSit2State = CheckboxStates.FindRef("Check_DoubleSit2");

			if (DoubleSit1State == ECheckBoxState::Checked)
			{
				FVector SofaLocation1 = FVector(-150.0f, 0.0f, 0.0f);
				FVector SofaLocation2 = FVector(150.0f, 0.0f, 0.0f);

				FTransform SofaTransform1;
				FTransform SofaTransform2;

				SofaTransform1.SetLocation(SofaLocation1);
				SofaTransform2.SetLocation(SofaLocation2);

				SofaTransform1.SetRotation(SofaRotation.Quaternion());
				SofaTransform2.SetRotation(SofaRotation.Quaternion());

				SofaTransform1.SetScale3D(FVector::OneVector);  // 스케일 1
				SofaTransform2.SetScale3D(FVector::OneVector);
			
				AKJS_BoxSofa* SpawnSofa = World->SpawnActor<AKJS_BoxSofa>(BoxSofa, SofaTransform1, params);
				AKJS_BoxSofa* SpawnSofa2 = World->SpawnActor<AKJS_BoxSofa>(BoxSofa, SofaTransform2, params);
			}

			else if (DoubleSit2State == ECheckBoxState::Checked)
			{
				FVector SofaLocation3 = FVector(0.0f, 0.0f, 0.0f);
				FTransform SofaTransform3;

				SofaTransform3.SetLocation(SofaLocation3);
				SofaTransform3.SetRotation(SofaRotation.Quaternion());
				SofaTransform3.SetScale3D(FVector::OneVector);

				AKJS_BoxSofa* SpawnSofa = World->SpawnActor<AKJS_BoxSofa>(BoxSofa, SofaTransform3, params);
			}
		}
	}

	//ServerOnLevelLoaded(LoadedWorld);
}


void UOSY_GameInstance::ReceiveLevelDataID(int LevelDataID)
{
	PlayId=LevelDataID;

	UE_LOG(LogTemp,Warning,TEXT("%d"),PlayId);
}

void UOSY_GameInstance::ParsePlayerData()
{
	parsePlayerData.ParseIntoArray(DataArray, TEXT(":"), true);

	id = FCString::Atoi(*DataArray[0]);
	name = DataArray[1];
	sub = DataArray[2];
	profileImage = DataArray[3];
	platform = DataArray[4];
	role = DataArray[5];
	email = DataArray[6];
}


//void UOSY_GameInstance::ServerOnLevelLoaded_Implementation(UWorld* LoadedWorld)
//{
//	MulticastOnLevelLoaded(LoadedWorld);
//}
//
//void UOSY_GameInstance::MulticastOnLevelLoaded_Implementation(UWorld* LoadedWorld)
//{
//	if (LoadedWorld->GetMapName() == "Box_indoor_Single" || LoadedWorld->GetMapName() == "Box_indoor_Multi" || LoadedWorld->GetMapName() == "StreetCar_Play")
//	{
//		UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
//	}
//
//	if (LoadedWorld->GetMapName().Contains("Box_indoor_Multi"))
//	{
//		UWorld* World = GetWorld();
//
//		if (World)
//		{
//			FActorSpawnParameters params;
//			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//			FRotator SofaRotation = FRotator::ZeroRotator; // 회전값 0
//			ECheckBoxState DoubleSit1State = CheckboxStates.FindRef("Check_DoubleSit1");
//			ECheckBoxState DoubleSit2State = CheckboxStates.FindRef("Check_DoubleSit2");
//
//			if (DoubleSit1State == ECheckBoxState::Checked)
//			{
//				FVector SofaLocation1 = FVector(-150.0f, 0.0f, 0.0f);
//				FVector SofaLocation2 = FVector(150.0f, 0.0f, 0.0f);
//
//				FTransform SofaTransform1;
//				FTransform SofaTransform2;
//
//				SofaTransform1.SetLocation(SofaLocation1);
//				SofaTransform2.SetLocation(SofaLocation2);
//
//				SofaTransform1.SetRotation(SofaRotation.Quaternion());
//				SofaTransform2.SetRotation(SofaRotation.Quaternion());
//
//				SofaTransform1.SetScale3D(FVector::OneVector);  // 스케일 1
//				SofaTransform2.SetScale3D(FVector::OneVector);
//
//				AKJS_BoxSofa* SpawnSofa = World->SpawnActor<AKJS_BoxSofa>(BoxSofa, SofaTransform1, params);
//				AKJS_BoxSofa* SpawnSofa2 = World->SpawnActor<AKJS_BoxSofa>(BoxSofa, SofaTransform2, params);
//			}
//
//			else if (DoubleSit2State == ECheckBoxState::Checked)
//			{
//				FVector SofaLocation3 = FVector(0.0f, 0.0f, 0.0f);
//				FTransform SofaTransform3;
//
//				SofaTransform3.SetLocation(SofaLocation3);
//				SofaTransform3.SetRotation(SofaRotation.Quaternion());
//				SofaTransform3.SetScale3D(FVector::OneVector);
//
//				AKJS_BoxSofa* SpawnSofa = World->SpawnActor<AKJS_BoxSofa>(BoxSofa, SofaTransform3, params);
//			}
//		}
//	}
//}
