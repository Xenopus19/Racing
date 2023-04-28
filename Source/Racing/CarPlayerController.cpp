// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(Controller, All, All)

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(IMCControls, 0);
		}

		MovementComponent = Cast<AWheeledVehiclePawn>(GetPawn())->GetVehicleMovementComponent();
		VelicleWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		VelicleWidget->AddToViewport(0);
	}
}

void ACarPlayerController::UpdateLap_Implementation(int Lap)
{
	OnLapUpdated.Broadcast(Lap);
}

void ACarPlayerController::Destroyed()
{
	Super::Destroyed();
	OnLapUpdated.Clear();
}
