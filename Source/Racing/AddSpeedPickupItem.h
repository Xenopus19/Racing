// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupItemBase.h"
#include "Car.h"
#include "AddSpeedPickupItem.generated.h"

UCLASS()
class RACING_API AAddSpeedPickupItem : public APickupItemBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int SpeedBonus = 10;
	
	virtual void DoPickupAction(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector Impulse, const FHitResult& Hit) override;
};
