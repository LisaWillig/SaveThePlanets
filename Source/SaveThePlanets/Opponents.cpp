// Fill out your copyright notice in the Description page of Project Settings.


#include "Opponents.h"
#include "Comet.h"
#include "DrawDebugHelpers.h"

// Sets default values
AOpponents::AOpponents()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOpponents::BeginPlay()
{
	Super::BeginPlay();
	SetSpawnTimer();
}

void AOpponents::SetSpawnTimer() {
	RepeatingCallsRemaining = 10;
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AOpponents::RepeatingFunction, SpawnRate, true, 1.0f);
	SpawnRate = SpawnRate / 2;

}
void AOpponents::RepeatingFunction()
{

	if (CometClass != nullptr) {
		FVector SpawnPoint = GenerateSpawnPoint();
		FRotator Rotation = GenerateSpawnRotation(SpawnPoint);
		auto enemy = GetWorld()->SpawnActor<AComet>(CometClass, SpawnPoint, Rotation);

		float mass = FMath::RandRange(100, 200);
		float size = FMath::RandRange(0.1f, 0.2f);
		float speed = FMath::RandRange(100, 500);

		enemy->SetParameters(mass, size, speed);
	}

    // Reset Timer with higher Spawnrate
    if (--RepeatingCallsRemaining <= 0){
		SetSpawnTimer();		
    }
}

FRotator AOpponents::GenerateSpawnRotation(FVector SpawnPoint) {
	FBox BoxPointInCircle = FBox(FVector(-250, -250, 0), FVector(250, 250, 0));
	FVector PointOnCircle = FMath::RandPointInBox(BoxPointInCircle);
	
	FVector InitialDirection = (PointOnCircle - SpawnPoint).GetSafeNormal();
	return InitialDirection.Rotation();
}

FVector AOpponents::GenerateSpawnPoint() {
	float xOne = FMath::RandRange(-1000, -750);
	float xTwo = FMath::RandRange(750, 1000);
	float yOne = FMath::RandRange(-1000, -750);
	float yTwo = FMath::RandRange(750, 1000);

	float quadrant = FMath::RandRange(0, 4);

	if (quadrant < 1) {
		return FVector(xOne, yOne, 0);
	}
	if (quadrant < 2) {
		return FVector(xTwo, yOne, 0);
	}
	if (quadrant < 3) {
		return FVector(xTwo, yTwo, 0);
	}
	return FVector(xOne, yTwo, 0);
}

// Called every frame
void AOpponents::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

