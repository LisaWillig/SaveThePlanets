// Fill out your copyright notice in the Description page of Project Settings.


#include "Comet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Planet.h"

// Sets default values
AComet::AComet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CometMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CometMesh"));

}

void AComet::BeginPlay()
{
	Super::BeginPlay();
	CometMesh->OnComponentBeginOverlap.AddDynamic(this, &AComet::OnOverlapBegin);
	//FVector Spawn = GenerateSpawnPoint();
	//rad = FMath::Abs(RotationVector());
	rad = 100;
	Velocity = GetActorForwardVector();
	//SetActorLocation(Spawn);
	mass = 10;
	UE_LOG(LogTemp, Warning, TEXT("Radius: %f"), rad)
}

// Called every frame
void AComet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ApplyRotation(DeltaTime);
	ApplyVelocity(DeltaTime);

}

void AComet::ApplyRotation(float DeltaTime) {
	float RotationAngle = Velocity.Size() * DeltaTime / (2 * rad); // in Radians
	FQuat RotationDelta(GetActorUpVector(), 2*RotationAngle);
	AddActorWorldRotation(RotationDelta);
	Velocity = RotationDelta.RotateVector(Velocity);
}

void AComet::ApplyVelocity(float DeltaTime) {
	float DeltaPosition = speed * DeltaTime;
	FVector Translation = DeltaPosition * Velocity;
	FHitResult HitResult;
	AddActorWorldOffset(Translation, true, &HitResult);
}


void AComet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	APlanet* Planet = Cast<APlanet>(OtherActor);
	if (Planet) {
		Planet->Collision(mass);
	}
	UE_LOG(LogTemp, Warning, TEXT("Collision! %s"), *OverlappedComp->GetName())
	this->Destroy();

}