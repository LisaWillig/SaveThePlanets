// Fill out your copyright notice in the Description page of Project Settings.


#include "Opponents.h"
#include "Comet.h"

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
		auto enemy = GetWorld()->SpawnActor<AComet>(CometClass, GenerateSpawnPoint(), FRotator());
	}

    /* Example for clearing Timer
    if (--RepeatingCallsRemaining <= 0){
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }*/


}

float AOpponents::GenerateSpawnRotation() {
	FBox BoxPointInCircle = FBox(FVector(-500, -500, 0), FVector(500, 500, 0));
	FVector PointOnCircle = FMath::RandPointInBox(BoxPointInCircle);
	float Radius = FMath::Sqrt(FMath::Square(PointOnCircle.X) + FMath::Square(PointOnCircle.Y));

	//A: Actor Location
	//B: Random Point in Level Area
	float alphaAngle = FMath::RandRange(1., 10); // Angle (Degree) at radius between A and B
	float betaAngle = FMath::RandRange(1., (179 - alphaAngle)); // Angle (Degree) at ActorLocation 

	/*
	float Radius = (FMath::Abs(FVector::Dist(GetActorLocation(), PointOnCircle)) * FMath::Sin(betaAngle)) / FMath::Sin(alphaAngle);
	UE_LOG(LogTemp, Warning, TEXT("Point To Cross: %s"), *PointOnCircle.ToCompactString())

		FVector InitialDirection = (PointOnCircle - GetActorLocation()).GetSafeNormal();
	FVector CurrentRotation = GetActorForwardVector();
	float rotate = FMath::Atan(CurrentRotation.X - InitialDirection.X);
	FQuat rotation = FQuat(GetActorUpVector(), rotate);
	SetActorRotation(rotation);
	*/
	return Radius;
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

