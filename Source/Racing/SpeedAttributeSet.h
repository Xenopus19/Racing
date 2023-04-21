// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "SpeedAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(SpeedAttributeSet, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(SpeedAttributeSet, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class RACING_API USpeedAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(USpeedAttributeSet, Speed)
};
