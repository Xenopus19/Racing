// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarPlayerController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Start.generated.h"

UCLASS()
class RACING_API AStart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStart();
	
	UPROPERTY(VisibleAnywhere, Category="Collision")
	UBoxComponent* Trigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="CheckpointCount")
	int CheckpointCount = 0;
	
	ACarPlayerController* PlayerController;
};
