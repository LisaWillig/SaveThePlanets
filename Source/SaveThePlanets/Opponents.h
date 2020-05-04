// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Opponents.generated.h"

UCLASS()
class SAVETHEPLANETS_API AOpponents : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpponents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTimerHandle TimerHandle;
	void RepeatingFunction();

	int RepeatingCallsRemaining = 10;
	FVector GenerateSpawnPoint();
	float GenerateSpawnRotation();

	UPROPERTY(EditDefaultsOnly, Category = "Comet")
	TSubclassOf<class AComet> CometClass;

};
