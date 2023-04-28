// Fill out your copyright notice in the Description page of Project Settings.


#include "Start.h"

#include <gameux.h>

#include "CarPawn.h"
#include "CarPlayerController.h"
#include "Kismet/GameplayStatics.h"
DEFINE_LOG_CATEGORY_STATIC(CarStart, All, All)

// Sets default values
AStart::AStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

// Called when the game starts or when spawned
void AStart::BeginPlay()
{
	Super::BeginPlay();
	
	if (Trigger)
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AStart::OnOverlapBegin);

	PlayerController = Cast<ACarPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AStart::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GetLocalRole() == ROLE_Authority)
	{
		ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
		int CurrentLap = CarPawn->GetLap();
		int CurrentCheckpoint = CarPawn->GetCheckpoint();
		CarPawn->ResetCheckpoint();

		if(CurrentCheckpoint != CheckpointCount && CurrentLap != -1)
			return;
		CurrentLap = CarPawn->GetLap();
		CarPawn->IncreaseLap();
		UE_LOG(CarStart, Display, TEXT("Lap: %d"), (CurrentLap + 1))
		ACarPlayerController* CarPlayerController = Cast<ACarPlayerController>(CarPawn->GetController());
		CarPlayerController->UpdateLap(CurrentLap + 1);
		
	}
}

// Called every frame
void AStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

