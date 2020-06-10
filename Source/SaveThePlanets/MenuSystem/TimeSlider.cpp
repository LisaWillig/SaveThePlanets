// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSlider.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "../UniverseGameInstance.h"


bool UTimeSlider::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(TimeSlider != nullptr)) return false;
	TimeSlider->OnValueChanged.AddDynamic(this, &UTimeSlider::SetTimeValue);

	GameInstance = Cast<UUniverseGameInstance>(GetGameInstance());

	return true;
}

void UTimeSlider::SetTimeValue(float time) {
	GameInstance->SetTime(time);
}

float UTimeSlider::GetTimeValue() {
	return Time;
}

void UTimeSlider::SetScore(int8 ScoreValue) {
	Score->SetText(FText::FromString(FString::FromInt(ScoreValue)));
}

void UTimeSlider::SetMultiplier(int8 MultiplierValue) {
	Multiplier->SetText(FText::FromString(FString::FromInt(MultiplierValue)));

}