// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"

bool UPauseMenu::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(ButtonRestart != nullptr)) return false;
	ButtonRestart->OnClicked.AddDynamic(this, &UPauseMenu::Start);

	if (!ensure(ButtonResume != nullptr)) return false;
	ButtonResume->OnClicked.AddDynamic(this, &UPauseMenu::Resume);

	if (!ensure(ButtonQuit != nullptr)) return false;
	ButtonQuit->OnClicked.AddDynamic(this, &UPauseMenu::Quit);

	if (!ensure(ButtonMainMenu != nullptr)) return false;
	ButtonMainMenu->OnClicked.AddDynamic(this, &UPauseMenu::TravelMainMenu);

	return true;
}

void UPauseMenu::Start() {
	if (MenuInterface == nullptr) return;
	MenuInterface->Start();
}

void UPauseMenu::Resume() {
	this->RemoveFromViewport();
}

void UPauseMenu::Quit() {
	if (MenuInterface == nullptr) return;
	MenuInterface->Quit();
}

void UPauseMenu::TravelMainMenu() {
	if (MenuInterface == nullptr) return;
	MenuInterface->TravelMainMenu();
}