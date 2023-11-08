// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "MoveComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Plugins/Runtime/XRBase/Source/XRBase/Public/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//VR카메라
	hmdCam = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	hmdCam->SetupAttachment(RootComponent);
	hmdCam->bAutoActivate = false;
	//VR카메라 메쉬
	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(hmdCam);

	StartCam = CreateDefaultSubobject<UCameraComponent>(TEXT("StartCam"));
	StartCam->SetupAttachment(RootComponent);
	
	//왼쪽 컨트롤러
	leftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Motion Controller"));
	leftMotionController->SetupAttachment(RootComponent);
	leftMotionController->SetTrackingMotionSource(FName("Left"));

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftMotionController);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempLeft(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
	if (TempLeft.Succeeded())
	{
		leftHand->SetSkeletalMesh(TempLeft.Object);
	}
	////////////////////////////////////////////////
	//오른쪽 컨트롤러
	rightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotionController->SetupAttachment(RootComponent);
	
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotionController);
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempRight(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if (TempRight.Succeeded())
	{
		rightHand->SetSkeletalMesh(TempRight.Object);
	}
	////////////////////////////////////////////////
	////////////////////////////////////////////////
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	//
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = false;
	
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"));

	////3인칭 카메라 세팅
	//Third_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("FollowCamera"));
	//Third_CameraBoom->SetupAttachment(RootComponent);
	//Third_CameraBoom->TargetArmLength = 10.0f;
	//Third_CameraBoom->bUsePawnControlRotation = true;
	//
	//Third_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third_FollowCamera"));
	//Third_FollowCamera->SetupAttachment(Third_CameraBoom);
	//Third_FollowCamera->bUsePawnControlRotation = false;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempThirdMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/DEV/KJS/Character/SitInChair/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (TempThirdMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempThirdMesh.Object);
	}
	
	//위젯 interaction
	WidgetInteractor = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget_Interactor"));
	WidgetInteractor->InteractionSource=EWidgetInteractionSource::Mouse;

	PlaylistWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayListWidget"));
	PlaylistWidget->SetupAttachment(RootComponent);
	ShowHostCodeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RoomCodeWidget"));
	ShowHostCodeWidget->SetupAttachment(RootComponent);
	EnterRoomWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnterCodeWidget"));
	EnterRoomWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		if (PlayerController != nullptr)
		{
			PlayerController->bShowMouseCursor = true;
		}
	}
	pc = GetController<APlayerController>();

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subSys)
		{
			subSys->AddMappingContext(imc_Mapping,0);
		}
	}

	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (MapName == "Yellow_Single")
	{
		// "Yellow_Single" 맵에서는 StartCam을 활성화합니다.
		StartCam->Activate();
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyCharacter::SwitchVRCamera, 3.5f, false);
	}
	else
	{
		// 그 외의 맵에서는 StartCam을 비활성화합니다.
		StartCam->Deactivate();
	}


	

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent != nullptr)
	{
		moveComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
	}

}

void AMyCharacter::SwitchVRCamera()
{
	if (pc)
	{
		if (APlayerCameraManager* pcm = pc->PlayerCameraManager)
		{
			pcm->StartCameraFade(0.f, 1.f, 1.0f, FColor::Black, false, true);

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, pcm]()
				{
					StartCam->Deactivate();
					hmdCam->Activate();
					

					pcm->StartCameraFade(1.0f, 0.0f, 3.0f, FColor::Black, false, true);
				}, 1.0f, false);
		}
	}
}

