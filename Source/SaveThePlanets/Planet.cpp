// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "CentralStar.h"
#include "DrawDebugHelpers.h"
#include "UniverseGameInstance.h"
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
	
    GameInstance = Cast<UUniverseGameInstance>(GetGameInstance());
    SetActorScale3D(FVector(Radius * 0.001));
    
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (MySun == nullptr) {
        GetTheSun();
    }

    float TimeControl = GameInstance->GetTime();
    calculateVeloctiy(DeltaTime* TimeControl);
}

void APlanet::calculateVeloctiy(float DeltaTime) {
    if (MySun == nullptr) {return;}

    float dist = FVector::Dist2D(GetActorLocation(), FVector(0, 0, 0))*0.01; // Distance in Meter
    float velocityMagnitude = GravityConstant* MySun->StarMass / dist;
    
    FVector DirectionForce = -(GetActorLocation().GetSafeNormal());
    FVector VelocityForce = FVector(DirectionForce.Y, -DirectionForce.X, 0);
   
    float winkel = velocityMagnitude* DeltaTime;
    float bogen = winkel / 360 * 2 * PI;

    float DeltaX = dist * FMath::Cos(FMath::DegreesToRadians(winkel));
    float DeltaY = dist * FMath::Sin(FMath::DegreesToRadians(winkel));
    FVector DeltaPosition = bogen * VelocityForce;
    FVector Test = FVector(DeltaX, DeltaY, 0);

    UE_LOG(LogTemp, Warning, TEXT("Test: %s"), *Test.ToCompactString())
    SetActorLocation(DeltaPosition + GetActorLocation());
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
       
