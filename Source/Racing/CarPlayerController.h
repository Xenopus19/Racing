// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CarPawn.h"
#include "ChaosVehicleMovementComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "WheeledVehiclePawn.h"
#include "CarPlayerController.generated.h"
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapEvent, int, Lap);

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
	UUserWidget* VelicleWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Lap events")
	FLapEvent OnLapUpdated;

	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void UpdateLap(int Lap);

	UPROPERTY(EditDefaultsOnly, Category="Spectator")
	TSubclassOf<AActor> SpectatorSpawn;

	UPROPERTY(EditDefaultsOnly, Category="Spectator")
	TSubclassOf<AActor> Spectator;

private:
	virtual void Destroyed() override;
};

