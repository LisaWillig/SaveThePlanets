// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Opponents.h"
#include "Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"
#include "Comet.generated.h"

USTRUCT()
struct FCometParameters
{
	GENERATED_USTRUCT_BODY()

	uint8 dayRotationSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	float speed = 10; //km 

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	float rad; //Circle intensity of original path 

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	float mass; //kg 

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	FVector GravityVelocity;

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	bool bCometIntention; // good: gain more points, bad: lose more points

};

UCLASS()
class SAVETHEPLANETS_API AComet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	FCometParameters CometParams;

	void SetParameters(float mass, float size, float speed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comet")
		UStaticMeshComponent* CometMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comet")
	bool bMaterial; 

private:

	FVector GenerateSpawnPoint();
	
	void ApplyVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime);
	void CheckPosition();

	UPROPERTY(EditDefaultsOnly, Category = "Comet")
	USoundCue* TestSound; 


	UPROPERTY(VisibleAnywhere, Category = "Comet")
		UCapsuleComponent* CapsuleComponent;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void GetTheSun();
	class ACentralStar* MySun;

	void ApplyStarGravity();

	UPROPERTY(EditDefaultsOnly, Category = "Comet")
	UParticleSystem* ExplosionEmitter;

};
