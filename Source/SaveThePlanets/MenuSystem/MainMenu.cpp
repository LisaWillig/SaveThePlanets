// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"


bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(MainStartButton != nullptr)) return false;
	MainStartButton->OnClicked.AddDynamic(this, &UMainMenu::Start);

	if (!ensure(MainHighscoreButton != nullptr)) return false;
	MainHighscoreButton->OnClicked.AddDynamic(this, &UMainMenu::Highscore);

	if (!ensure(MainQuitButton != nullptr)) return false;
	MainQuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

	return true;
}

void UMainMenu::Start() {
	if (MenuInterface == nullptr) return;
	MenuInterface->Start();
}

void UMainMenu::Highscore() {
	if (MenuInterface == nullptr) return;
	MenuInterface->TravelHighscoreMenu();
}

void UMainMenu::Quit() {
	if (MenuInterface == nullptr) return;
	MenuInterface->Quit();
}