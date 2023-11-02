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
    // LoadedData�� �����Ͱ� ����˴ϴ�.
	//}
}

void UOSY_GameInstance::Init()
{
	Super::Init();

	//Online Session Interface API ���ٿ� �ν��Ͻ� ��������
	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		sessionInterface = subsys->GetSessionInterface();

		//���� �̺�Ʈ�� �Լ� ���ε� �ϱ�
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
	//LAN ��������, DEDICATED�������� ����
	settings.bIsDedicated = false;
	settings.bIsLANMatch = true;
	
	//�˻� ������ ������ �����Ѵ�.
	settings.bShouldAdvertise = true;

	//�ڱ� ������ ���޵� �� �ְ� �����Ѵ�.
	settings.bUsesPresence = true;

	//�ٸ� ������ �߰� ������ ����Ѵ�.
	settings.bAllowJoinInProgress = true;
	settings.bAllowJoinViaPresence = true;

	//���� ���� �ο��� �����Ѵ�.
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

