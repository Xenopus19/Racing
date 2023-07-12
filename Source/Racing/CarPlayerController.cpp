// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPlayerController.h"
#include "RacingGameStateBase.h"

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
		VehicleWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		VehicleWidget->AddToViewport(0);
	}

	if (GetLocalRole() == ROLE_Authority)
	{
		AActor* FoundSpectator = UGameplayStatics::GetActorOfClass(GetWorld(), SpectatorSpawn);
		FVector Location = FoundSpectator->GetActorLocation();
		FActorSpawnParameters const SpawnInfo;
		AActor* SpawnedSpectator = GetWorld()->SpawnActor<AActor>(Location, FRotator::ZeroRotator);
		Possess(Cast<APawn>(SpawnedSpectator));
	}
}

void ACarPlayerController::UpdateLap_Implementation(int Lap)
{
	OnLapUpdated.Broadcast(Lap);
}

void ACarPlayerController::ShowPlayerRank_Implementation(int Rank)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Show player rank"));
	OnRaceFinished.Broadcast();
}

void ACarPlayerController::ProceedLapUpdating(int Lap)
{
	UpdateLap(Lap);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Proceed Lap Updating"));

	if (Cast<ARacingGameStateBase>(GetGameInstance()->GetWorld()->GetGameState())->DidPlayerFinishRace(Lap))
	{
		ShowPlayerRank(Cast<ARacingGameStateBase>(GetGameInstance()->GetWorld()->GetGameState())->GetPlayersFinishedRace());
	}
}



void ACarPlayerController::Destroyed()
{
	Super::Destroyed();
	OnLapUpdated.Clear();
}
