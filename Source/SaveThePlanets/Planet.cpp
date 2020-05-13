// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "CentralStar.h"
#include "DrawDebugHelpers.h"
#include "UniverseGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlanetCollision"));
    CapsuleComponent->InitCapsuleSize(Radius * 0.05, Radius * 0.05);
    RootComponent = PlanetMesh;
   
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
    GameInstance = Cast<UUniverseGameInstance>(GetGameInstance());
    SetActorScale3D(FVector(Radius * 0.001));
    Distance = FVector::Dist2D(GetActorLocation(), FVector(0, 0, 0)) * 0.01;
    dayRotationSpeed = FMath::RandRange(1, 100);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (MySun == nullptr) {
        GetTheSun();
    }

    float TimeControl = GameInstance->GetTime();

    applyLocationOffset(DeltaTime*TimeControl);
    applyRotationOffset(DeltaTime * TimeControl);
}

void APlanet::applyLocationOffset(float DeltaTime) {
    if (MySun == nullptr) {return;}

    float const dist = FVector::Dist2D(GetActorLocation(), FVector(0, 0, 0)) * 0.01; // Distance in Meter
    float const velocityMagnitude = GravityConstant * MySun->StarMass / dist;

    FVector const DirectionForce = -(GetActorLocation().GetSafeNormal());
    FVector const VelocityForce = FVector(DirectionForce.Y, -DirectionForce.X, 0);

    float const DeltaAngle = velocityMagnitude * DeltaTime;
    float const DeltaCirclePath = DeltaAngle / 360 * 2 * PI;
    FVector const DeltaPosition = DeltaCirclePath * VelocityForce;

    /*  when the Time is large, so the angle to cross is big, 
        the approximation that Deltav = v* Delta_angle is not valid anymore
        As a result, the planets would move outwards in a spiral, 
        the higher the angle eg. "time" is.
     */
    FVector const ErrorCorrection = (dist - Distance) * DirectionForce;

    SetActorLocation(DeltaPosition + GetActorLocation()+ErrorCorrection);
    CapsuleComponent->SetWorldTransform(GetActorTransform());
}

void APlanet::applyRotationOffset(float DeltaTime)
{
    FRotator Rotatevelocity = PlanetMesh->GetComponentRotation();
    Rotatevelocity.Yaw = Rotatevelocity.Yaw + DeltaTime * dayRotationSpeed;
    PlanetMesh->SetRelativeRotation(Rotatevelocity);
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
       
void APlanet::Collision(float mass) {
    PlanetMass = PlanetMass - mass;
    if (PlanetMass <= 0) {
        auto Instance = Cast<UUniverseGameInstance>(GetGameInstance());
        if (Instance != nullptr) {
            this->Destroy();
            Instance->GameOver();
        }
    }
}