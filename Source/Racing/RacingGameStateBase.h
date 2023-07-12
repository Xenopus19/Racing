// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RacingGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class RACING_API ARacingGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool DidPlayerFinishRace(int PlayerLap);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		int GetPlayersFinishedRace();
};
