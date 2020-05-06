// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API USaveData : public USaveGame
{
	GENERATED_BODY()
	
public:

	USaveData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
	int HighscoreSAVE;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
};
