// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SaveThePlanetsGameModeBase.h"
#include "UniverseGameInstance.h"

void ASaveThePlanetsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASaveThePlanetsGameModeBase::CountHighScore, 1.0f, true, 1.0f);
	gameInstance = Cast<UUniverseGameInstance>(GetGameInstance());
	
}

void ASaveThePlanetsGameModeBase::CountHighScore() {
	if (gameInstance != nullptr) {
		if (gameInstance->bGameStart == true) {
			Score = Score + 1 * ScoreMultiplayer;
			gameInstance->SetScore(Score);
			gameInstance->SetMultiplier(ScoreMultiplayer);
		}
	}
	else {
		gameInstance = Cast<UUniverseGameInstance>(GetGameInstance());
	}

}

