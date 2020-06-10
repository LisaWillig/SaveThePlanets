// Fill out your copyright notice in the Description page of Project Settings.


#include "Comet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Planet.h"
#include "CentralStar.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "SaveThePlanetsGameModeBase.h"


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
	CometParams.bCometIntention = bMaterial;
	GetTheSun();
}

// Called every frame
void AComet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyRotation(DeltaTime);
	ApplyStarGravity();
	ApplyVelocity(DeltaTime);
	
	CheckPosition();
}

void AComet::CheckPosition() {
	FVector Location = GetActorLocation();
	if (Location.GetMax() > 1500 || Location.GetMin() < -1500) {
		Destroy();
	}
}

void AComet::ApplyRotation(float DeltaTime) {
	float RotationAngle = CometParams.Velocity.Size() * DeltaTime / (CometParams.rad); // in Radians
	FQuat RotationDelta(GetActorUpVector(), RotationAngle);
	AddActorWorldRotation(RotationDelta);
	CometParams.Velocity = RotationDelta.RotateVector(CometParams.Velocity);
}

void AComet::SetParameters(float setMass, float size, float setSpeed) {
	CometParams.Velocity = GetActorForwardVector();
	CometParams.rad = FMath::RandRange(3, 15);
	CometParams.mass = setMass;
	SetActorScale3D(FVector(size, size, size));
	CometParams.speed = setSpeed;

}

void AComet::GetTheSun() {
	TArray<AActor*> Stars;
	TSubclassOf< ACentralStar > CentralStar;
	CentralStar = ACentralStar::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CentralStar, Stars);
	if (Stars[0] != nullptr) {
		MySun = Cast<ACentralStar>(Stars[0]);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Sun!"))
	}
}

void AComet::ApplyStarGravity() {

	if (MySun == nullptr) { return; }
	float const dist = FVector::Dist2D(GetActorLocation(), FVector(0, 0, 0)) * 0.01; // Distance in Meter
	float const velocityMagnitude = (MySun->StarMass* CometParams.mass) / (dist*dist);
	FVector const Direction = -(GetActorLocation().GetSafeNormal());
	CometParams.GravityVelocity = Direction * velocityMagnitude;
}
void AComet::ApplyVelocity(float DeltaTime) {
	float DeltaPosition = CometParams.speed * DeltaTime;
	CometParams.Velocity = CometParams.Velocity + CometParams.GravityVelocity*0.0000005;
	FVector Translation = DeltaPosition * CometParams.Velocity;
	FHitResult HitResult;
	AddActorWorldOffset(Translation, true, &HitResult);
}


void AComet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	APlanet* Planet = Cast<APlanet>(OtherActor);
	if (Planet) {
		if (CometParams.bCometIntention == false) {
			Planet->Collision(CometParams.mass);
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				ExplosionEmitter,
				GetActorTransform(),
				true,
				EPSCPoolMethod::AutoRelease,
				true
			);
			UGameplayStatics::PlaySound2D(
				GetWorld(),
				TestSound);

			this->Destroy();
			return;
		}
		else {
			auto gameMode = Cast<ASaveThePlanetsGameModeBase>(GetWorld()->GetAuthGameMode());

			if (gameMode != nullptr) { gameMode->ScoreMultiplayer++; }
			Planet->Collision(CometParams.mass/3);
			//Game Instance Multiplier
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				ExplosionEmitter,
				GetActorTransform(),
				true,
				EPSCPoolMethod::AutoRelease,
				true
			);
			UGameplayStatics::PlaySound2D(
				GetWorld(),
				TestSound,
				1.0f,
				2.0f);
			this->Destroy();
			return;
		}
	}
	ACentralStar* Star = Cast<ACentralStar>(OtherActor);

	if (Star) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionEmitter,
			GetActorTransform(),
			true,
			EPSCPoolMethod::AutoRelease,
			true
		);
		UGameplayStatics::PlaySound2D(
			GetWorld(),
			TestSound);
		Destroy();	
	}
}