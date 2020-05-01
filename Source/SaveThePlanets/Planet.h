// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

UCLASS()
class SAVETHEPLANETS_API APlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void calculateVeloctiy(float DeltaTime);

	class ACentralStar* MySun;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Planet")
	UStaticMeshComponent* PlanetMesh;

	UPROPERTY(EditAnywhere, Category = "Planet")
	float PlanetMass = 100; //kg 

	UPROPERTY(EditAnywhere, Category = "Planet")
	float Radius = 1000; //km (UMRECHNEN!) 

	UPROPERTY(EditAnywhere, Category = "Planet")
	float Distance = 100; //km (UMRECHNEN!) 

	UPROPERTY(EditAnywhere, Category = "Planet")
	float GravityConstant = 1; // 6.678 * 10^-11 m^3/kg s^2

	void GetTheSun();
};
