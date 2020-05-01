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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Star")
	UStaticMeshComponent* StarMesh;

	UPROPERTY(EditAnywhere, Category = "Star")
	float StarMass = 1000; //kg 
};
