// Fill out your copyright notice in the Description page of Project Settings.


#include "HighscoreMenu.h"
#include "Components/Button.h"

bool UHighscoreMenu::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UHighscoreMenu::MainMenu);

	return true;
}

void UHighscoreMenu::MainMenu() {
	if (MenuInterface == nullptr) return;
	MenuInterface->TravelMainMenu();
}
