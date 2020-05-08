// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Opponents.h"
#include "Components/CapsuleComponent.h"
#include "Comet.generated.h"

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

	FVector GenerateSpawnPoint();
	void SetParameters(float mass, float size, float speed);
	void ApplyVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime);
	float RotationVector();
	void CheckPosition();

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	UStaticMeshComponent* CometMesh;

	UPROPERTY(VisibleAnywhere, Category = "Comet")
	UCapsuleComponent* CapsuleComponent;

	FVector Velocity;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float mass;
	float rad;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float speed = 10;
};
