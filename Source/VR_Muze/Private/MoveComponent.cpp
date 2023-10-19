// Fill out your copyright notice in the Description page of Project Settings.

#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "MyCharacter.h"
#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player = GetOwner<AMyCharacter>();
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Triggered, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Completed, this, &UMoveComponent::Move);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UMoveComponent::Rotate);
	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Completed, this, &UMoveComponent::Rotate);

}

void UMoveComponent::Move(const struct FInputActionValue& value)
{
	if(player)
	{
		FVector2D controllerInput = value.Get<FVector2D>();

		FVector forwardVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::X);
		FVector rightVec = FRotationMatrix(player->pc->GetControlRotation()).GetUnitAxis(EAxis::Y);


		player->AddMovementInput(forwardVec, controllerInput.X);
		player->AddMovementInput(rightVec, controllerInput.Y);
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
		}
	}
}




