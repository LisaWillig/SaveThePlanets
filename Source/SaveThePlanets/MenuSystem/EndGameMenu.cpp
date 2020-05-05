// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameMenu.h"
#include "Components/Button.h"
#include "../UniverseGameInstance.h"
#include "Components/TextBlock.h"

bool UEndGameMenu::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(RestartButton != nullptr)) return false;
	RestartButton->OnClicked.AddDynamic(this, &UEndGameMenu::Start);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UEndGameMenu::Quit);

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UEndGameMenu::TravelMainMenu);

	auto gameInstance = Cast<UUniverseGameInstance>(GetWorld()->GetGameInstance());
	if (gameInstance != nullptr) {
		Score = gameInstance->Score;
	}
	TextScore->SetText(FText::AsNumber(Score));

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