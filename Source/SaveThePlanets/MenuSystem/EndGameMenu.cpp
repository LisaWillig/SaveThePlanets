// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameMenu.h"
#include "Components/Button.h"

bool UEndGameMenu::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(RestartButton != nullptr)) return false;
	RestartButton->OnClicked.AddDynamic(this, &UEndGameMenu::Start);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UEndGameMenu::Quit);

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UEndGameMenu::TravelMainMenu);

	return true;
}

void UEndGameMenu::Start() {
	if (MenuInterface == nullptr) return;
	MenuInterface->Start();
}

void UEndGameMenu::Quit() {
	if (MenuInterface == nullptr) return;
	MenuInterface->Quit();
}

void UEndGameMenu::TravelMainMenu() {
	if (MenuInterface == nullptr) return;
	MenuInterface->TravelMainMenu();
}