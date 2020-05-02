// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UniverseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UUniverseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    
    UUniverseGameInstance();

    UFUNCTION(BlueprintCallable)
    void LoadSlider();

    void SetTime(float NewTime);
    float GetTime();

private:

    TSubclassOf<class UUserWidget> SliderClass;
    void QuitGame();

    class UMenuWidget* Slider;

    void Setup(class UMenuWidget* Slider);

    float TimeValue;
};
