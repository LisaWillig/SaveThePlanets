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




    //PlanetParams = PlanetParameters();
    
    RootComponent = PlanetMesh;
   
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
    GameInstance = Cast<UUniverseGameInstance>(GetGameInstance());

    InitializePlanetParams();
}

void APlanet::InitializePlanetParams()
{
    PlanetParams.Radius = FMath::RandRange(500, 1500);
    CapsuleComponent->InitCapsuleSize(PlanetParams.Radius * 0.05, PlanetParams.Radius * 0.05); //calc from m too cm
    SetActorScale3D(FVector(PlanetParams.Radius * 0.001));
    PlanetParams.Distance = FVector::Dist2D(GetActorLocation(), FVector(0, 0, 0)) * 0.01; // m to cm
    PlanetParams.dayRotationSpeed = FMath::RandRange(1, 100);
    PlanetParams.PlanetMass = FMath::RandRange(1, 5) * PlanetParams.Radius / 10;
    PlanetParams.PlanetIntegrity = PlanetParams.PlanetMass / 100;
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
    FVector const ErrorCorrection = (dist - PlanetParams.Distance) * DirectionForce;

    SetActorLocation(DeltaPosition + GetActorLocation()+ErrorCorrection);
    CapsuleComponent->SetWorldTransform(GetActorTransform());
}

void APlanet::applyRotationOffset(float DeltaTime)
{
    FRotator Rotatevelocity = PlanetMesh->GetComponentRotation();
    Rotatevelocity.Yaw = Rotatevelocity.Yaw + DeltaTime * PlanetParams.dayRotationSpeed;
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
    PlanetParams.PlanetIntegrity = PlanetParams.PlanetIntegrity - (PlanetParams.PlanetIntegrity/mass);
    if (PlanetParams.PlanetIntegrity <= 0) {
        auto Instance = Cast<UUniverseGameInstance>(GetGameInstance());
        if (Instance != nullptr) {
            this->Destroy();
            Instance->GameOver();
        }
    }
}