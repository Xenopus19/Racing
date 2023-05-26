// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPlayerController.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(Controller, All, All)

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Vehicle = Cast<ACarPawn>(GetPawn());
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(IMCControls, 0);
		}

		MovementComponent = Vehicle->GetVehicleMovementComponent();
		VelicleWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		VelicleWidget->AddToViewport(0);
	}

	if (GetLocalRole() == ROLE_Authority)
	{
		AActor* FoundSpectator = UGameplayStatics::GetActorOfClass(GetWorld(), SpectatorSpawn);
		FVector Location = FoundSpectator->GetActorLocation();
		FActorSpawnParameters const SpawnInfo;
		AActor* SpawnedSpectator = GetWorld()->SpawnActor<AActor>(Location, FRotator::ZeroRotator);
		Possess(Cast<APawn>(SpawnedSpectator));
		//haha delay ne haha(((
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
