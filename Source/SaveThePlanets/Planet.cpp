// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "CentralStar.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (MySun == nullptr) {
        GetTheSun();
    }

    calculateVeloctiy(DeltaTime);
}

void APlanet::calculateVeloctiy(float DeltaTime) {
    if (MySun == nullptr) {return;}
    float dist = FVector::Dist2D(GetActorLocation(), FVector(0, 0, 0))*0.01; // Distance in Meter
    float velocityMagnitude = GravityConstant * MySun->StarMass/ dist;

    FVector DirectionForce = -(GetActorLocation().GetSafeNormal());
    UE_LOG(LogTemp, Warning, TEXT("Force Direction: %s"), *DirectionForce.ToCompactString())

    FVector VelocityForce = FVector(DirectionForce.Y, -DirectionForce.X, 0);
    UE_LOG(LogTemp, Warning, TEXT("Velocity Direction: %s"), *VelocityForce.ToCompactString())

    const UWorld* World = GetWorld();
    if (World != nullptr) { DrawDebugLine(World, GetActorLocation(), VelocityForce, FColor(255, 50, 50, 1), false, 2, 2, 5); }
    UE_LOG(LogTemp, Warning, TEXT("Are Othogonal? %i"), FVector::Orthogonal(VelocityForce, DirectionForce))
        //if (World != nullptr) { DrawDebugLine(World, DirectionForce, GetActorLocation(), FColor(255, 50, 50, 1), true, 2, 2, 5); }

    FVector NewPos = VelocityForce * velocityMagnitude;
    UE_LOG(LogTemp, Warning, TEXT("NewPos? %s"), *NewPos.ToCompactString())
    SetActorLocation(NewPos);
}

void APlanet::GetTheSun() {
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
       
