// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSlider.h"
#include "Components/Slider.h"
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