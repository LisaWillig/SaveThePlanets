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
	RootComponent= CometMesh;
}

void AComet::BeginPlay()
{
	Super::BeginPlay();
	CometMesh->OnComponentBeginOverlap.AddDynamic(this, &AComet::OnOverlapBegin);
	Velocity = GetActorForwardVector();
}

// Called every frame
void AComet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ApplyRotation(DeltaTime);
	ApplyVelocity(DeltaTime);

	CheckPosition();

}

void AComet::CheckPosition() {
	FVector Location = GetActorLocation();
	if (Location.GetMax() > 1000 || Location.GetMin() < -1000) {
		UE_LOG(LogTemp, Warning, TEXT("Destroyed"))
		Destroy();
	}
}
void AComet::ApplyRotation(float DeltaTime) {
	float RotationAngle = Velocity.Size() * DeltaTime / (2 * 10); // in Radians
	FQuat RotationDelta(GetActorUpVector(), 2*RotationAngle);
	AddActorWorldRotation(RotationDelta);
	Velocity = RotationDelta.RotateVector(Velocity);
}

void AComet::SetParameters(float setMass, float size, float setSpeed) {
	this->mass = setMass;
	SetActorScale3D(FVector(size, size, size));
	this->speed = setSpeed;
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
		this->Destroy();
		return;
	}

}