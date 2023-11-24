// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "MyCharacter.h"
#include "Components/WidgetInteractionComponent.h"
#include "MediaLobbyWidget.h"
#include "Components/WidgetComponent.h"
#include "KJS_TypeInviteNumWidget.h"
#include "KJS_EnterRoomWidget.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AMyCharacter>();

}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Triggered, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Completed, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Completed, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Started, this, &UMoveComponent::PressTrigger);
	enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Started, this, &UMoveComponent::ReleaseTrigger);
	enhancedInputComponent->BindAction(inputActions[3], ETriggerEvent::Started, this, &UMoveComponent::VisibiltyPlaylistWidget);
	//enhancedInputComponent->BindAction(inputActions[4], ETriggerEvent::Started, this, &UMoveComponent::InputOuputRoomCodeWidget);
	
}

void UMoveComponent::Move(const struct FInputActionValue& value)
{
	if(player)
	{
		//FVector2D controllerInput = value.Get<FVector2D>();
		//
		//FVector forwardVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::X);
		//FVector rightVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::Y);
		//
		//const FRotator Rotation = player->Controller->GetControlRotation();
		//const FRotator YawRotation(0,Rotation.Yaw, 0);
		//
		//player->AddMovementInput(forwardVec, controllerInput.Y);
		//player->AddMovementInput(rightVec, controllerInput.X);
	}

}

void UMoveComponent::Rotate(const struct FInputActionValue& value)
{
	if(player)
	{
		FVector2D rightConInput = value.Get<FVector2D>();
		if (player->pc != nullptr)
		{
			player->pc->AddYawInput(rightConInput.X);
			player->pc->AddPitchInput(rightConInput.Y);
	
			player->AddControllerYawInput(rightConInput.X);
			player->AddControllerPitchInput(rightConInput.Y);
		}
	}
}

void UMoveComponent::VisibiltyPlaylistWidget(const struct FInputActionValue& value)
{
	bool isPlaylistVisible = player->PlaylistWidget->IsVisible();

	player->PlaylistWidget->SetVisibility(!isPlaylistVisible);

	UE_LOG(LogTemp, Warning, TEXT("Visible Playlist!!!"));
}

//void UMoveComponent::InputOuputRoomCodeWidget(const struct FInputActionValue& value)
//{
//	bool isEnterRoomVisible = player->EnterRoomWidget->IsVisible();
//	bool isHostWidgetVisible = player->ShowHostCodeWidget->IsVisible();
//
//	player->EnterRoomWidget->SetVisibility(!isEnterRoomVisible);
//	player->ShowHostCodeWidget->SetVisibility(!isHostWidgetVisible);
//
//	UE_LOG(LogTemp, Warning, TEXT("Visible RoomCodeWidget!!!"));
//}

void UMoveComponent::PressTrigger()
{
	player->WidgetInteractor->PressPointerKey(EKeys::LeftMouseButton);
	UE_LOG(LogTemp, Warning, TEXT("Press Pointer!!!"));

}

void UMoveComponent::ReleaseTrigger()
{
		player->WidgetInteractor->ReleasePointerKey(EKeys::LeftMouseButton);
		UE_LOG(LogTemp, Warning, TEXT("Release Pointer!!!"));
}


