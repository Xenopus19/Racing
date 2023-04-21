// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "CarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RACING_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
    	
public:
	ACarPlayerController();
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* IMCControls;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GAS")
	TSubclassOf<UGameplayEffect> InitSpeedEffect;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(UGameplayEffect* Effect);

protected:
	virtual void PostInitializeComponents() override;
};

