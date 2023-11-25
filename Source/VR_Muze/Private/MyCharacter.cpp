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
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Runtime/CinematicCamera/Public/CineCameraActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "KJS_GameModeBase.h"
#include "OSY_GameInstance.h"
#include "Net/UnrealNetwork.h"
#include "KJS_MuzePlayerState.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//VR카메라
	hmdCam = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	hmdCam->SetupAttachment(RootComponent);
	hmdCam->bAutoActivate = true;
	//VR카메라 메쉬
	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(hmdCam);
	hmdMesh->SetVisibility(false);

	//StartCam = CreateDefaultSubobject<UCameraComponent>(TEXT("StartCam"));
	//StartCam->SetupAttachment(RootComponent);
	//StarthmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarthmdMesh"));
	//StarthmdMesh->SetupAttachment(StartCam);
	//StartCam->bAutoActivate = true;

	CustomizeCam = CreateDefaultSubobject<UCameraComponent>(TEXT("CustomizeCam"));
	CustomizeCam->SetupAttachment(RootComponent);
	CustomizeCam->bAutoActivate = false;
	CustomizeCam->SetRelativeLocation(FVector(480.0f, 0.0f, 35.f));
	CustomizeCam->SetFieldOfView(35.0f);

	
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
	rightMotionController->SetTrackingMotionSource(FName("Right"));
	
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotionController);

	rightHand->bOnlyOwnerSee = true;
	rightHand->bOwnerNoSee = false;
	leftHand->bOnlyOwnerSee = true;
	leftHand->bOwnerNoSee = false;
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempRight(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if (TempRight.Succeeded())
	{
		rightHand->SetSkeletalMesh(TempRight.Object);
	}
	////////////////////////////////////////////////
	////////////////////////////////////////////////
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempThirdMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/DEV/KJS/Character/Character/Idle.Idle'"));
	if (TempThirdMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempThirdMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}
	
	//위젯 interaction
	WidgetInteractor = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget_Interactor"));
	WidgetInteractor->InteractionSource=EWidgetInteractionSource::World;
	WidgetInteractor->SetupAttachment(rightHand);

	PlaylistWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayListWidget"));
	PlaylistWidget->SetupAttachment(RootComponent);
	//PlaylistWidget->SetVisibility(false);
	//ShowHostCodeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RoomCodeWidget"));
	//ShowHostCodeWidget->SetupAttachment(RootComponent);
	//EnterRoomWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnterCodeWidget"));
	//EnterRoomWidget->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USoundBase>TempSound(TEXT("/Script/Engine.SoundWave'/Game/DEV/KJS/PC_Widget/WidgetSound/Netflix-Intro_cut.Netflix-Intro_cut'"));

	IdleAnimation = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/DEV/KJS/Character/Character/Animation/Idle.Idle"));
	SittingAnimation = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/DEV/KJS/Character/Character/Animation/SittingAnim.SittingAnim"));
	SittingIdle = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/DEV/KJS/Character/Character/Animation/Sitting_Idle.Sitting_Idle"));
	//////////////////////////////////////////////////////////////////////////////////

	AttachedGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Glass"));
	AttachedGlass->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GlassSocket"));

	AttachedHat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat"));
	AttachedHat->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HatSocket"));

	AttachedTie = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tie"));
	AttachedTie->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("TieSocket"));

	//////////////////////////////////////////////////////////////////////////////////
	ai = UKJS_CharacterAnimInstance::StaticClass();
	//////////////////////////////////////////////////////////////////////////////////
	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempBlack(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Black.Body_Black'"));
	if (TempBlack.Succeeded())
	{
		BodyMaterials.Add(TempBlack.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempWhite(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_White.Body_White'"));
	if (TempWhite.Succeeded())
	{
		BodyMaterials.Add(TempWhite.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempBlue(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_SkyBlue.Body_SkyBlue'"));
	if (TempBlue.Succeeded())
	{
		BodyMaterials.Add(TempBlue.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempPink(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Pink.Body_Pink'"));
	if (TempPink.Succeeded())
	{
		BodyMaterials.Add(TempPink.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempYellow(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Yellow.Body_Yellow'"));
	if (TempYellow.Succeeded())
	{
		BodyMaterials.Add(TempYellow.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempGreen(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Green.Body_Green'"));
	if (TempGreen.Succeeded())
	{
		BodyMaterials.Add(TempGreen.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempDeepYellow(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_DeepYellow.Body_DeepYellow'"));
	if (TempDeepYellow.Succeeded())
	{
		BodyMaterials.Add(TempDeepYellow.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempViolet(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Violet.Body_Violet'"));
	if (TempViolet.Succeeded())
	{
		BodyMaterials.Add(TempViolet.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempCoral(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Coral.Body_Coral'"));
	if (TempCoral.Succeeded())
	{
		BodyMaterials.Add(TempCoral.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstance>TempNavy(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/DEV/KJS/Character/Character/Material/Body_Navy.Body_Navy'"));
	if (TempNavy.Succeeded())
	{
		BodyMaterials.Add(TempNavy.Object);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHat1(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/HAT/meSH/HAT1.HAT1'"));
	if(TempHat1.Succeeded())
	{
		HatMeshes.Add(TempHat1.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHat2(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/HAT/meSH/HAT2.HAT2'"));
	if (TempHat2.Succeeded())
	{
		HatMeshes.Add(TempHat2.Object);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass1(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass1.Glass1'"));
	if (TempGlass1.Succeeded())
	{
		GlassMeshes.Add(TempGlass1.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass2(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass2.Glass2'"));
	if (TempGlass2.Succeeded())
	{
		GlassMeshes.Add(TempGlass2.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass3(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass3.Glass3'"));
	if (TempGlass3.Succeeded())
	{
		GlassMeshes.Add(TempGlass3.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass4(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass4.Glass4'"));
	if (TempGlass4.Succeeded())
	{
		GlassMeshes.Add(TempGlass4.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass5(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass5.Glass5'"));
	if (TempGlass5.Succeeded())
	{
		GlassMeshes.Add(TempGlass5.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass6(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass6.Glass6'"));
	if (TempGlass6.Succeeded())
	{
		GlassMeshes.Add(TempGlass6.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempGlass7(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Glasses/Glass7.Glass7'"));
	if (TempGlass7.Succeeded())
	{
		GlassMeshes.Add(TempGlass7.Object);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempTie1(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Tie/BowTie.BowTie'"));
	if (TempTie1.Succeeded())
	{
		TieMeshes.Add(TempTie1.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempTie2(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Tie/BowTie2.BowTie2'"));
	if (TempTie2.Succeeded())
	{
		TieMeshes.Add(TempTie2.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempTie3(TEXT("/Script/Engine.StaticMesh'/Game/ART/Ocean/Customize/Tie/BowTie3.BowTie3'"));
	if (TempTie3.Succeeded())
	{
		TieMeshes.Add(TempTie3.Object);
	}

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UOSY_GameInstance>(GetGameInstance());
	ps = Cast<AKJS_MuzePlayerState>(GetPlayerState());


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (PlayerController != nullptr)
		{
			PlayerController->bShowMouseCursor = true;
		}
	}
	pc = GetController<APlayerController>();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);


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

	if (MapName == "Box_indoor_Single")
	{
		UGameplayStatics::PlaySound2D(this,enterSound);
		rightHand->SetVisibility(false);
		leftHand->SetVisibility(false);
		hmdMesh->SetVisibility(false);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyCharacter::SwitchVRCamera, 16.5f, false);
	}

	if (MapName == "CustomizeMap"||MapName.Contains("CH_MAP"))
	{
		hmdCam->Deactivate();
		CustomizeCam->Activate();
	}

	UKJS_CharacterAnimInstance* AnimInstance = Cast<UKJS_CharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	}

	if (MapName.Contains("CH_MAP"))
	{
		GetMesh()->PlayAnimation(IdleAnimation, false);
	}

	else if (MapName.Contains("Box_indoor_Single"))
	{
		GetMesh()->PlayAnimation(SittingAnimation, false);
	}
	else if (MapName.Contains("Box_indoor_Multi"))
	{
		GetMesh()->PlayAnimation(SittingIdle, true);
		SetVisibiltyMesh();
	}
	
	if (gi)
	{
		SwitchBodyColor(gi->color);
		AttachHat(gi->hat);
		AttachGlass(gi->face);
		AttachTie(gi->tie);
	}


	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &AMyCharacter::ChangeFOV);
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
	//if (enhancedInputComponent != nullptr)
	//{
	//	moveComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
	//}
	if (enhancedInputComponent != nullptr && moveComp != nullptr && inputActions.Num() > 0)
	{
		moveComp->SetupPlayerInputComponent(enhancedInputComponent, inputActions);
	}
}

void AMyCharacter::SwitchVRCamera()
{
	if (pc)
	{
		rightHand->SetVisibility(true);
		leftHand->SetVisibility(true);
		hmdMesh->SetVisibility(true);
		GetMesh()->SetVisibility(false);
		AttachedGlass->SetVisibility(false);
		AttachedHat->SetVisibility(false);
		AttachedTie->SetVisibility(false);
		//if (APlayerCameraManager* pcm = pc->PlayerCameraManager)
		//{
		//	//pcm->StartCameraFade(0.f, 1.f, 3.0f, FColor::Black, false, true);
		//
		//	FTimerHandle TimerHandle;
		//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, pcm]()
		//		{
		//			
		//		}, 1.0f, false);
		//}
	}
}

void AMyCharacter::ChangeFOV(UWorld* LoadedWorld)
{
	
	// Get the current level name
	FString CurrentLevel = LoadedWorld->GetMapName();
	CurrentLevel.RemoveFromStart(LoadedWorld->StreamingLevelsPrefix);


	// Check if the camera component is valid
	if (hmdCam)
	{
		if (CurrentLevel == "StreetCar_Play")
		{
			// Set the camera's FOV to 35 when entering 'MyLevel'
			hmdCam->SetFieldOfView(35.0f);
		}
		else
		{
			// Reset the camera's FOV when leaving 'MyLevel'
			hmdCam->SetFieldOfView(90.0f);  // Change this to your default FOV value
		}
	}
}


void AMyCharacter::SwitchBodyColor(int32 Index)
{
	ServerSwtichBodyColor(Index);
}

void AMyCharacter::AttachGlass(int32 Index)
{
	ServerAttachGlass(Index);
}

void AMyCharacter::AttachHat(int32 Index)
{
	ServerAttachHat(Index);
}

void AMyCharacter::AttachTie(int32 Index)
{
	ServerAttachTie(Index);
}

void AMyCharacter::SetVisibiltyMesh()
{
	ServerSetVisibiltyMesh();
}

void AMyCharacter::ServerSwtichBodyColor_Implementation(int32 Index)
{
	ColorIndex = Index;
	MulticastSwitchBodyColor(ColorIndex);
}


void AMyCharacter::MulticastSwitchBodyColor_Implementation(int32 Index)
{
	ColorIndex = Index;
	GetMesh()->SetMaterial(0, BodyMaterials[Index]);
	if (ps)
	{
		ColorIndex = ps->ColorIndex;
	}
}

void AMyCharacter::ServerAttachGlass_Implementation(int32 Index)
{
	GlassIndex = Index;
	MulticastAttachGlass(GlassIndex);
}


void AMyCharacter::MulticastAttachGlass_Implementation(int32 Index)
{
	GlassIndex = Index;
	AttachedGlass->SetStaticMesh(GlassMeshes[Index]);
	if (ps)
	{
		GlassIndex = ps->GlassIndex;
	}
}

void AMyCharacter::ServerAttachHat_Implementation(int32 Index)
{
	HatIndex = Index;
	MulticastAttachHat(HatIndex);
}

void AMyCharacter::MulticastAttachHat_Implementation(int32 Index)
{
	HatIndex = Index;
	AttachedHat->SetStaticMesh(HatMeshes[Index]);
	if (ps)
	{
		HatIndex = ps->HatIndex;
	}
}

void AMyCharacter::ServerAttachTie_Implementation(int32 Index)
{
	TieIndex = Index;
	MulticastAttachTie(TieIndex);
}

void AMyCharacter::MulticastAttachTie_Implementation(int32 Index)
{
	TieIndex = Index;
	AttachedTie->SetStaticMesh(TieMeshes[Index]);
	if (ps)
	{
		TieIndex = ps->TieIndex;
	}
}

void AMyCharacter::ServerSetVisibiltyMesh_Implementation()
{
	MulticastSetVisibiltyMesh();
}

void AMyCharacter::MulticastSetVisibiltyMesh_Implementation()
{
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bOnlyOwnerSee = false;
	AttachedGlass->bOwnerNoSee = true;
	AttachedHat->bOwnerNoSee = true;
	AttachedTie->bOwnerNoSee = true;
	AttachedGlass->bOnlyOwnerSee = false;
	AttachedHat->bOnlyOwnerSee = false;
	AttachedTie->bOnlyOwnerSee = false;
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, ColorIndex);
	DOREPLIFETIME(AMyCharacter, HatIndex);
	DOREPLIFETIME(AMyCharacter, GlassIndex);
	DOREPLIFETIME(AMyCharacter, TieIndex);
}

