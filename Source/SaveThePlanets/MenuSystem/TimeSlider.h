// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "TimeSlider.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UTimeSlider : public UMenuWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	class USlider* TimeSlider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Multiplier;

	UFUNCTION()
	void SetTimeValue(float time);

	float Time;

	class UUniverseGameInstance* GameInstance;

protected:

	UFUNCTION()
	float GetTimeValue();


	virtual bool Initialize() override;

public:
	void SetScore(int8 ScoreValue);
	void SetMultiplier(int8 MultiplierValue);

};
