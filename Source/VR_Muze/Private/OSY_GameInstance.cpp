// Fill out your copyright notice in the Description page of Project Settings.


#include "OSY_GameInstance.h"
#include "OSY_PropWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"


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

void UOSY_GameInstance::Init()
{
	Super::Init();

	//Online Session Interface API 접근용 인스턴스 가져오기
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		sessionInterface = subsys->GetSessionInterface();

		//세션 이벤트에 함수 바인딩 하기
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOSY_GameInstance::OnCreatedMuzeSession);
		/*FTimerHandle createHandler;
		GetWorld()->GetTimerManager().SetTimer(createHandler, this, &UOSY_GameInstance::CreateMuzeSession, 1, false);*/
	}

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UOSY_GameInstance::OnLevelLoaded);

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

void UOSY_GameInstance::CreateMuzeSession(FText roomName, int32 playerCount)
{
	FOnlineSessionSettings settings;
	//LAN 연결인지, DEDICATED연결인지 설정
	settings.bIsDedicated = false;
	settings.bIsLANMatch = true;
	
	//검색 가능한 방으로 설정한다.
	settings.bShouldAdvertise = true;

	//자기 정보를 전달될 수 있게 설정한다.
	settings.bUsesPresence = true;

	//다른 유저의 중간 입장을 허용한다.
	settings.bAllowJoinInProgress = true;
	settings.bAllowJoinViaPresence = true;

	//입장 가능 인원을 설정한다.
	settings.NumPublicConnections = playerCount;
	//bool isSuccess = sessionInterface->CreateSession(0, FText(roomName, ToString()), settings);
	//UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));


}

void UOSY_GameInstance::OnCreatedMuzeSession(FName sessionName, bool bWasSuccessful)
{
	//if (bWasSuccessful)
	//{
	//	bool result = GetWorld()->ServerTravel("/Game/DEV/KJS/Box?Listen");
	//	UE_LOG(LogTemp, Warning, TEXT("Travel Result : %s"), result ? *FString("Success") : *FString("Failed"));
	//}
}

void UOSY_GameInstance::OnLevelLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld->GetMapName() == "5_Box")
	{
		UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
	}
}

