// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
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
	ACarPawn();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GAS", ReplicatedUsing=OnRep_AbilitySystemComponent)
	UAbilitySystemComponent* AbilitySystemComponent;

	UFUNCTION()
    void OnRep_AbilitySystemComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	TSubclassOf<UGameplayEffect> InitSpeedEffect;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(UGameplayEffect* Effect);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void IncreaseCheckpoint();
	void ResetCheckpoint();
	int GetCheckpoint() const;
	int GetLap() const;
	void IncreaseLap();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ApplySpeedChanges(float Speed);
	
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

	UPROPERTY(EditDefaultsOnly, Category="Material")
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionBreak;
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionHandBrake;
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionLookAround;
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionReset;
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionSteering;
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionThrottle;
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputAction* InputActionToggleCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	UInputMappingContext* IMCControls;

private:
	int CurrentCheckpoint = 0;
	
	UPROPERTY(Replicated)
	int CurrentLap = -1;

	bool HasCameraChanged = false;

	FTransform FindResetTransform();
	void InterpsToOriginalRotation();
	void BrakeLights(bool BrakeLights);

	void BindActions(UEnhancedInputComponent* Input);

	void BreakStarted(const FInputActionInstance& Instance);
	void BreakTriggered(const FInputActionInstance& Instance);
	void BreakCompleted(const FInputActionInstance& Instance);
	void HandBrakeTriggered(const FInputActionInstance& Instance);
	void HandBrakeCompleted(const FInputActionInstance& Instance);
	void LookAround(const FInputActionInstance& Instance);
	void ResetRotation(const FInputActionInstance& Instance);
	void Steering(const FInputActionInstance& Instance);
	void Throttle(const FInputActionInstance& Instance);
	void ToggleCamera(const FInputActionInstance& Instance);

	void ApplyEffectsChanges(const FActiveGameplayEffect& EffectRemoved);
	void ApplyEffectsChanges();
};

inline ACarPawn::ACarPawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

