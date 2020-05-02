// Fill out your copyright notice in the Description page of Project Settings.


#include "UniverseGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/TimeSlider.h"
#include "MenuSystem/MenuWidget.h"
#include "Components/Slider.h"

UUniverseGameInstance::UUniverseGameInstance() {

	ConstructorHelpers::FClassFinder<UUserWidget> SliderBPClass(TEXT("/Game/HUD/WBP_Slider"));
	if (!ensure(SliderBPClass.Class != nullptr))return;
	SliderClass = SliderBPClass.Class;
}

void UUniverseGameInstance::QuitGame() {
	auto* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;
	playerController->ConsoleCommand("quit");
}

void UUniverseGameInstance::LoadSlider() {
	UE_LOG(LogTemp, Warning, TEXT("Loading Slider"))
	if (!ensure(SliderClass != nullptr))return;
	Slider = CreateWidget<UMenuWidget>(this, SliderClass);
	if (!ensure(Slider != nullptr))return;
	Slider->Setup();
}

void UUniverseGameInstance::SetTime(float NewTime) {
	TimeValue = NewTime;
}

float UUniverseGameInstance::GetTime() {
	return TimeValue;
}