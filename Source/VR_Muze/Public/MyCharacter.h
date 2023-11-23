// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "InputActionValue.h"
#include "KJS_CharacterAnimInstance.h"
#include "MyCharacter.generated.h"

//class UInputMappingContext;
//class UInputAction;
//struct FInputActionValue;

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
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputMappingContext* DefaultMappingContext;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* InputTrigger;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* VisibilityPlaylist;

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
	class UWidgetInteractionComponent* WidgetInteractor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UWidgetComponent* PlaylistWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UOSY_GameInstance* gi;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	//class UWidgetComponent* ShowHostCodeWidget;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	//class UWidgetComponent* EnterRoomWidget;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	//class UCameraComponent* StartCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UStaticMeshComponent* StarthmdMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UCameraComponent* CustomizeCam;

public:
	UPROPERTY()
	class APlayerController* pc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UMoveComponent* moveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputMappingContext* imc_Mapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TArray<class UInputAction*> inputActions;

	UPROPERTY()
	class ULevelSequencePlayer* SequencePlayer;

	// Sequence Assets
	UPROPERTY(EditAnywhere)
	class ULevelSequence* SequenceAsset;

	UPROPERTY(EditAnywhere)
	class USoundBase* enterSound;

	UFUNCTION()
	void SwitchVRCamera();

	UFUNCTION()
	void PlayLevelSequence();

	UFUNCTION()
	void SetViewToCineCamera();

	UFUNCTION()
	void ChangeFOV(UWorld* LoadedWorld);

	UPROPERTY(EditDefaultsOnly, Category = Animation)
    TSubclassOf<UKJS_CharacterAnimInstance> ai;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
    class UAnimSequence* IdleAnimation;

    UPROPERTY(EditDefaultsOnly, Category = Animation)
	class UAnimSequence* SittingAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	class UAnimSequence* SittingIdle;

	UPROPERTY()
    class UAnimSequence* AnimToPlay;
	/// <summary>
	/// //////////////////////////////////////////////////////////////////
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customize")
    TArray<UMaterialInstance*> BodyMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customize")
	TArray<UStaticMesh*> HatMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customize")
	TArray<UStaticMesh*> GlassMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customize")
	TArray<UStaticMesh*> TieMeshes;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customize")
	class UStaticMeshComponent* AttachedGlass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customize")
	class UStaticMeshComponent* AttachedHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customize")
	class UStaticMeshComponent* AttachedTie;

	///////////////////////////////////////////////////////////////
	UFUNCTION()
	void SwitchBodyColor(int32 Index);

	UFUNCTION()
	void AttachGlass(int32 Index);

	UFUNCTION()
	void AttachHat(int32 Index);

	UFUNCTION()
	void AttachTie(int32 Index);

	//UStaticMeshComponent* CreateMeshComponent(UStaticMesh* Mesh, const FName& SocketName);
};
