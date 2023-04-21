// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "SpeedAttributeSet.h"

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
	}

	ApplyGameplayEffect(InitSpeedEffect.GetDefaultObject());
	
}

ACarPlayerController::ACarPlayerController()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ACarPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<USpeedAttributeSet>();
	}
}

void ACarPlayerController::ApplyGameplayEffect(UGameplayEffect* Effect)
{
	FGameplayEffectContextHandle handle;
	AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect, 0, handle);
	
}
