// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"

#include "CarPawn.h"
DEFINE_LOG_CATEGORY_STATIC(CheckPoint, All, All)
// Sets default values
ACheckPoint::ACheckPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverlapBegin);
}

void ACheckPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GetLocalRole() == ROLE_Authority)
	{
		ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
		int CurrentCheckpoint = CarPawn->GetCheckpoint();
		if(CurrentCheckpoint + 1 == CheckpointNumber)
		{
			UE_LOG(CheckPoint, Display, TEXT("Checkpoint %d"), CheckpointNumber)
			CarPawn->IncreaseCheckpoint();
		}
	}
}

void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

