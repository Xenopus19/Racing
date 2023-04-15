// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "CarPawn.generated.h"

struct FInputActionInstance;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class RACING_API ACarPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* FrontCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* BackCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* BackSpringArm1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* FrontSpringArm2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	USkeletalMeshComponent* CarMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VehicleComponent")
	UChaosVehicleMovementComponent* ChaosVehicleMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Material")
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionBreak;
	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionHandBrake;
	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionLookAround;
	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionReset;
	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionSteering;
	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionThrottle;
	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputAction* InputActionToggleCamera;

	UPROPERTY(EditAnywhere, Category = "Actions")
	UInputMappingContext* IMCControls;

private:
	bool HasCameraChanged = false;

	void InterpsToOriginalRotation();
	void BrakeLights(bool BrakeLights);
	FTransform FindResetTransform();

	void BindActions(UEnhancedInputComponent* Input);

	void BreakStarted(const FInputActionInstance& Instance);
	void BreakTriggered(const FInputActionInstance& Instance);
	void BreakCompleted(const FInputActionInstance& Instance);
	void HandBrakeTriggered(const FInputActionInstance& Instance);
	void HandBrakeCompleted(const FInputActionInstance& Instance);
	void LookAround(const FInputActionInstance& Instance);
	void Reset(const FInputActionInstance& Instance);
	void Steering(const FInputActionInstance& Instance);
	void Throttle(const FInputActionInstance& Instance);
	void ToggleCamera(const FInputActionInstance& Instance);
};

