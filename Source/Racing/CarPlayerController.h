// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CarPawn.h"
#include "ChaosVehicleMovementComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "WheeledVehiclePawn.h"
#include "CarPlayerController.generated.h"
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapEvent, int, Lap);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRaceFinishedEvent);

UCLASS()
class RACING_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
    	
public:
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* IMCControls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle")
	UChaosVehicleMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite, Category="Vehicle")
	ACarPawn* Vehicle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UUserWidget* VehicleWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Lap events")
	FLapEvent OnLapUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "Lap events")
	FRaceFinishedEvent OnRaceFinished;

	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void UpdateLap(int Lap);

	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void ShowPlayerRank(int Rank);

	UPROPERTY(EditDefaultsOnly, Category="Spectator")
	TSubclassOf<AActor> SpectatorSpawn;

	UPROPERTY(EditDefaultsOnly, Category="Spectator")
	TSubclassOf<AActor> Spectator;

	UFUNCTION(BlueprintCallable)
	void ProceedLapUpdating(int Lap);

	UFUNCTION(BlueprintCallable)
	void CreateUI();

private:


	virtual void Destroyed() override;
};

