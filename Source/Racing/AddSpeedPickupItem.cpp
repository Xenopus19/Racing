// Fill out your copyright notice in the Description page of Project Settings.


#include "AddSpeedPickupItem.h"

void AAddSpeedPickupItem::DoPickupAction(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector Impulse, const FHitResult& Hit)
{
	Super::DoPickupAction(HitComponent, Other, OtherComp, Impulse, Hit);
}
