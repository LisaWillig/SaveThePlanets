// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "SaveThePlanetsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API ASaveThePlanetsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void CountHighScore();

	FTimerHandle TimerHandle;
	float Score;
	int8 ScoreMultiplayer = 1;
	class UUniverseGameInstance* gameInstance;
};
