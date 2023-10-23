// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class VR_MUZE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UCameraComponent* hmdCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UStaticMeshComponent* hmdMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UMotionControllerComponent* leftMotionController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UMotionControllerComponent* rightMotionController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class USpringArmComponent* Third_CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UCameraComponent* Third_FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UWidgetInteractionComponent* WidgetInteractor;

public:
	class APlayerController* pc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UMoveComponent* moveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputMappingContext* imc_Mapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TArray<class UInputAction*> inputActions;


};
