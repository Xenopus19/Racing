// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemBase.h"

// Sets default values
APickupItemBase::APickupItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupItemBase::BeginPlay()
{
	Super::BeginPlay();

	ThisMesh = FindComponentByClass<UStaticMeshComponent>();
	
	ThisMesh->OnComponentHit.AddDynamic(this, &APickupItemBase::DoPickupAction);
}

void APickupItemBase::DoPickupAction(UPrimitiveComponent* HitComponent, AActor* Other, UPrimitiveComponent* OtherComp, FVector Impulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Collided with something")));
}
