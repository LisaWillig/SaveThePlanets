// Fill out your copyright notice in the Description page of Project Settings.


#include "CentralStar.h"

// Sets default values
ACentralStar::ACentralStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarMesh"));
}

// Called when the game starts or when spawned
void ACentralStar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACentralStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

