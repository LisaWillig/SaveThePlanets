// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Planet.generated.h"


USTRUCT()
struct FPlanetParameters
{
	GENERATED_USTRUCT_BODY()

	uint8 dayRotationSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Planet")
	float Radius; //km 

	UPROPERTY(VisibleAnywhere, Category = "Planet")
	float PlanetMass; //kg 

	float PlanetIntegrity; //kg 

	UPROPERTY(VisibleAnywhere, Category = "Planet")
	float Distance; //km 

};


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
	void InitializePlanetParams();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:	

	void Collision(float mass);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgress;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,  Category = "Planet")
	UStaticMeshComponent* PlanetMesh;

	UPROPERTY(VisibleAnywhere, Category = "Planet")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "Planet")
	float GravityConstant = 1; // 6.678 * 10^-11 m^3/kg s^2

	UPROPERTY(EditDefaultsOnly, Category = "Planet")
	FPlanetParameters PlanetParams;

	UPROPERTY(EditDefaultsOnly, Category = "Comet")
	UParticleSystem* ExplosionEmitter;

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	class UWidgetComponent* HealthBar;

	void UpdateHealthBar();
	void ShowHealthBar();
	int8 RepeatingCallsRemaining;
	FTimerHandle HealthBarTimerHandle;

private:

	void GetTheSun();
	void applyLocationOffset(float DeltaTime);
	void applyRotationOffset(float DeltaTime);

	class ACentralStar* MySun;
	class UUniverseGameInstance* GameInstance;


	
};
