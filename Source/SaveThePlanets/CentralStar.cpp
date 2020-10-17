// Fill out your copyright notice in the Description page of Project Settings.


#include "CentralStar.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UniverseGameInstance.h"

// Sets default values
ACentralStar::ACentralStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarMesh"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("StarCollision"));
	CapsuleComponent->InitCapsuleSize(100, 100);
	RootComponent = StarMesh;
}

// Called when the game starts or when spawned
void ACentralStar::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UUniverseGameInstance>(GetGameInstance());
	dayRotationSpeed = FMath::RandRange(5, 20);
}

// Called every frame
void ACentralStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TimeControl = GameInstance->GetTime();
	applyRotationOffset(TimeControl * DeltaTime);


}

void ACentralStar::applyRotationOffset(float DeltaTime)
{
	FRotator Rotatevelocity = StarMesh->GetComponentRotation();
	Rotatevelocity.Yaw = Rotatevelocity.Yaw + DeltaTime * dayRotationSpeed;
	StarMesh->SetRelativeRotation(Rotatevelocity);
}