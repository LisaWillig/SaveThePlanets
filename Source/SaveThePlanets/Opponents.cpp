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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AOpponents::RepeatingFunction, 1.0f, true, 1.0f);
	
}

void AOpponents::RepeatingFunction()
{
	if (CometClass != nullptr) {
		FVector SpawnPoint = GenerateSpawnPoint();
		FRotator Rotation = GenerateSpawnRotation(SpawnPoint);
		auto enemy = GetWorld()->SpawnActor<AComet>(CometClass, SpawnPoint, Rotation);

		float mass = FMath::RandRange(1, 100);
		float size = FMath::RandRange(0.05f, 0.2f);
		float speed = FMath::RandRange(10, 500);

		enemy->SetParameters(mass, size, speed);
	}

    /* Example for clearing Timer
    if (--RepeatingCallsRemaining <= 0){
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }*/


}

FRotator AOpponents::GenerateSpawnRotation(FVector SpawnPoint) {
	FBox BoxPointInCircle = FBox(FVector(-500, -500, 0), FVector(500, 500, 0));
	FVector PointOnCircle = FMath::RandPointInBox(BoxPointInCircle);

	//A: Actor Location
	//B: Random Point in Level Area
	float alphaAngle = FMath::RandRange(1., 40); // Angle (Degree) at radius between A and B
	float betaAngle = FMath::RandRange(1., (179 - alphaAngle)); // Angle (Degree) at ActorLocation 

	float Radius = (FVector::Dist(SpawnPoint, PointOnCircle) * FMath::Sin(betaAngle)) / FMath::Sin(alphaAngle);
	FVector CenterCircle = FVector(SpawnPoint.X + FMath::Sin(90 - alphaAngle) * Radius, SpawnPoint.Y + FMath::Sin(90 - betaAngle) * Radius, 0);

	FVector InitialDirection = (PointOnCircle - SpawnPoint).GetSafeNormal();
	FVector CurrentRotation = GetActorForwardVector();
	float rotate = FMath::Atan(CurrentRotation.X - InitialDirection.X);
	FQuat rotation = FQuat(FVector(0,0,1), rotate);
	const FMatrix TransformMatrix;
	DrawDebugCircle(
		GetWorld(),
		CenterCircle,
		Radius,
		50,
		FColor(0, 0, 255, 1),
		true,
		100.f,
		1,
		10,
		FVector(1, 0, 0),
		FVector(0, 1, 0),
		true);
	return rotation.Rotator();
}

FVector AOpponents::GenerateSpawnPoint() {
	float xOne = FMath::RandRange(-750, -500);
	float xTwo = FMath::RandRange(500, 750);
	float yOne = FMath::RandRange(-750, -500);
	float yTwo = FMath::RandRange(500, 750);

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

