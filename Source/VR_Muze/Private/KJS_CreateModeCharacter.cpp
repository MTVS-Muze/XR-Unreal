// Fill out your copyright notice in the Description page of Project Settings.


#include "KJS_CreateModeCharacter.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"

// Sets default values
AKJS_CreateModeCharacter::AKJS_CreateModeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UInputAction>TempMove(TEXT("/Script/EnhancedInput.InputAction'/Game/DEV/KJS/Character/Input/IA_PlayerMove.IA_PlayerMove'"));
	if (TempMove.Succeeded())
	{
		MoveAction = TempMove.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction>TempLook(TEXT("/Script/EnhancedInput.InputAction'/Game/DEV/KJS/Character/Input/IA_PlayerRotation.IA_PlayerRotation'"));
	if (TempMove.Succeeded())
	{
		LookAction = TempLook.Object;
	}

}

// Called when the game starts or when spawned
void AKJS_CreateModeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (PlayerController != nullptr)
		{
			PlayerController->bShowMouseCursor = true;
		}
	}

}

// Called every frame
void AKJS_CreateModeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKJS_CreateModeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKJS_CreateModeCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKJS_CreateModeCharacter::Look);

	}
}

void AKJS_CreateModeCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);


	}
}

void AKJS_CreateModeCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

