// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CentralStar.generated.h"

UCLASS()
class SAVETHEPLANETS_API ACentralStar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACentralStar();

	UPROPERTY(EditAnywhere, Category = "Star")
	float StarMass = 10000; //kg 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	class UUniverseGameInstance* GameInstance;
	void applyRotationOffset(float DeltaTime);

	UPROPERTY(VisibleAnywhere, Category = "Star")
	class UStaticMeshComponent* StarMesh;

	UPROPERTY(VisibleAnywhere, Category = "Star")
	class UCapsuleComponent* CapsuleComponent;

	uint8 dayRotationSpeed; 


};
