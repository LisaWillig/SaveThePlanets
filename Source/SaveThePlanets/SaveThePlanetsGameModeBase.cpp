// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SaveThePlanetsGameModeBase.h"


void ASaveThePlanetsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASaveThePlanetsGameModeBase::CountHighScore, 1.0f, true, 1.0f);
}

void ASaveThePlanetsGameModeBase::CountHighScore() {
	Score++;
	UE_LOG(LogTemp, Warning, TEXT("Score: %f"), Score)
}

void ASaveThePlanetsGameModeBase::clearTimerHighScore() {
	GetWorldTimerManager().ClearTimer(TimerHandle);
}