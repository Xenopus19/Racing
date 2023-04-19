// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

DEFINE_LOG_CATEGORY_STATIC(Car, All, All)

void ACarPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	BindActions(Input);
}

void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UNavMovementComponent* MovementComponent = Cast<UNavMovementComponent>(ChaosVehicleMovementComponent);
	if (MovementComponent)
	{
		float InDampimg = MovementComponent->IsMovingOnGround() ? 0 : 3;
		CarMesh->SetAngularDamping(InDampimg);
		InterpsToOriginalRotation();
	}
}

void ACarPawn::BrakeLights(bool BrakeLights)
{
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	CarMesh->SetMaterial(0, DynamicMaterial);
	float Value = BrakeLights ? 200 : 40;
	DynamicMaterial->SetScalarParameterValue("BrakeLightPower", Value);
}

FTransform ACarPawn::FindResetTransform()
{
	FVector NewLocation = GetActorLocation() + FVector(0, 0, 50);
	FRotator NewRotation = FRotator(0, GetActorRotation().Yaw, 0);
	return FTransform(NewRotation, NewLocation, FVector(1, 1, 1));
}

void ACarPawn::InterpsToOriginalRotation()
{
	float Yaw = BackSpringArm1->GetRelativeRotation().Yaw;
	float NewYaw = FMath::FInterpTo(Yaw, 0, GetWorld()->GetDeltaSeconds(), 1);
	BackSpringArm1->SetRelativeRotation(FRotator(0, NewYaw, 0));
}

void ACarPawn::BindActions(UEnhancedInputComponent* Input)
{
	Input->BindAction(InputActionBreak, ETriggerEvent::Started, this, &ACarPawn::BreakStarted);
	Input->BindAction(InputActionBreak, ETriggerEvent::Triggered, this, &ACarPawn::BreakTriggered);
	Input->BindAction(InputActionBreak, ETriggerEvent::Completed, this, &ACarPawn::BreakCompleted);
	Input->BindAction(InputActionHandBrake, ETriggerEvent::Triggered, this, &ACarPawn::HandBrakeTriggered);
	Input->BindAction(InputActionHandBrake, ETriggerEvent::Completed, this, &ACarPawn::HandBrakeCompleted);
	Input->BindAction(InputActionLookAround, ETriggerEvent::Triggered, this, &ACarPawn::LookAround);
	Input->BindAction(InputActionReset, ETriggerEvent::Started, this, &ACarPawn::Reset);
	Input->BindAction(InputActionSteering, ETriggerEvent::Triggered, this, &ACarPawn::Steering);
	Input->BindAction(InputActionSteering, ETriggerEvent::Completed, this, &ACarPawn::Steering);
	Input->BindAction(InputActionThrottle, ETriggerEvent::Triggered, this, &ACarPawn::Throttle);
	Input->BindAction(InputActionThrottle, ETriggerEvent::Completed, this, &ACarPawn::Throttle);
	Input->BindAction(InputActionToggleCamera, ETriggerEvent::Started, this, &ACarPawn::ToggleCamera);
}

void ACarPawn::BreakStarted(const FInputActionInstance& Instance)
{
	BrakeLights(true);
}

void ACarPawn::BreakTriggered(const FInputActionInstance& Instance)
{
	float FloatValue = Instance.GetValue().Get<float>();
	ChaosVehicleMovementComponent->SetBrakeInput(FloatValue);
}

void ACarPawn::BreakCompleted(const FInputActionInstance& Instance)
{
	BrakeLights(false);
	ChaosVehicleMovementComponent->SetBrakeInput(0);
}

void ACarPawn::HandBrakeTriggered(const FInputActionInstance& Instance)
{
	ChaosVehicleMovementComponent->SetHandbrakeInput(true);
	BrakeLights(true);
}

void ACarPawn::HandBrakeCompleted(const FInputActionInstance& Instance)
{
	ChaosVehicleMovementComponent->SetHandbrakeInput(false);
	BrakeLights(false);
}

void ACarPawn::LookAround(const FInputActionInstance& Instance)
{
	float FloatValue = Instance.GetValue().Get<float>();
	BackSpringArm1->AddLocalRotation(FRotator(0, FloatValue, 0));
}

void ACarPawn::Reset(const FInputActionInstance& Instance)
{
	this->SetActorTransform(FindResetTransform(), false, nullptr, ETeleportType::TeleportPhysics);
	CarMesh->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
	CarMesh->SetPhysicsLinearVelocity(FVector::Zero());
}

void ACarPawn::Steering(const FInputActionInstance& Instance)
{
	float FloatValue = Instance.GetValue().Get<float>();
	ChaosVehicleMovementComponent->SetSteeringInput(FloatValue);
}

void ACarPawn::Throttle(const FInputActionInstance& Instance)
{
	float FloatValue = Instance.GetValue().Get<float>();
	ChaosVehicleMovementComponent->SetThrottleInput(FloatValue);
}

void ACarPawn::ToggleCamera(const FInputActionInstance& Instance)
{
	HasCameraChanged = !HasCameraChanged;
	FrontCamera->Deactivate();
	BackCamera->Deactivate();
	if (HasCameraChanged)
	{
		FrontCamera->Activate();
		return;
	}
	BackCamera->Activate();
}

