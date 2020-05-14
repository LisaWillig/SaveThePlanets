// Fill out your copyright notice in the Description page of Project Settings.


#include "UniverseGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/TimeSlider.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/HighscoreMenu.h"
#include "MenuSystem/PauseMenu.h"
#include "MenuSystem/EndGameMenu.h"
#include "Components/Slider.h"
#include "SaveThePlanetsGameModeBase.h"
#include "Kismet/GameplayStatics.h"


UUniverseGameInstance::UUniverseGameInstance() {

	ConstructorHelpers::FClassFinder<UUserWidget> SliderBPClass(TEXT("/Game/HUD/WBP_Slider"));
	if (!ensure(SliderBPClass.Class != nullptr))return;
	SliderClass = SliderBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/HUD/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))return;
	MainMenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> HighscoreBPClass(TEXT("/Game/HUD/WBP_Highscore"));
	if (!ensure(HighscoreBPClass.Class != nullptr))return;
	HighscoreClass = HighscoreBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(TEXT("/Game/HUD/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr))return;
	PauseMenuClass = PauseMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> EndGameMenuBPClass(TEXT("/Game/HUD/WBP_GameOver"));
	if (!ensure(EndGameMenuBPClass.Class != nullptr))return;
	EndGameMenuClass = EndGameMenuBPClass.Class;
}


void UUniverseGameInstance::LoadSlider() {
	if (!ensure(SliderClass != nullptr))return;
	Slider = CreateWidget<UMenuWidget>(this, SliderClass);
	if (!ensure(Slider != nullptr))return;
	Slider->Setup();
}

void UUniverseGameInstance::RefocusSlider() {
	if (Slider != nullptr) {
		Slider->SetFocus();
	}
}

void UUniverseGameInstance::SetTime(float NewTime) {
	TimeValue = NewTime;
}

float UUniverseGameInstance::GetTime() {
	return TimeValue;
}

void UUniverseGameInstance::TravelMainMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel("/Game/Maps/MainMenuLevel", ETravelType::TRAVEL_Absolute);
}

void UUniverseGameInstance::LoadMainMenu() {
	if (!ensure(MainMenuClass != nullptr))return;
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!ensure(MainMenu != nullptr))return;
	MainMenu->Setup();
	MainMenu->SetMenuInterface(this);
}

void UUniverseGameInstance::TravelHighscoreMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel("/Game/Maps/HighScoreLevel", ETravelType::TRAVEL_Absolute);
}

void UUniverseGameInstance::LoadHighscoreMenu() {
	if (!ensure(HighscoreClass != nullptr))return;
	auto HighscoreMenu = CreateWidget<UHighscoreMenu>(this, HighscoreClass);
	if (!ensure(HighscoreMenu != nullptr))return;
	HighscoreMenu->Setup();
	HighscoreMenu->SetMenuInterface(this);
}

void UUniverseGameInstance::LoadPauseMenu() {
	if (!ensure(PauseMenuClass != nullptr))return;
	auto PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
	if (!ensure(PauseMenu != nullptr))return;

	PauseMenu->Setup();
	PauseMenu->SetMenuInterface(this);
	UWorld* World = GetWorld();
	if (World != nullptr) {
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void UUniverseGameInstance::GameOver() {
	auto gameMode = Cast<ASaveThePlanetsGameModeBase>(GetWorld()->GetAuthGameMode());
	
	if (gameMode != nullptr) {
		gameMode->clearTimerHighScore();
		Score = gameMode->Score;
		if (Score > HighScore) {
			HighScore = Score;
			//UE_LOG(LogTemp, Warning, TEXT("Highscore: %f, Score: %f"), HighScore, Score)
			saveHighScore(HighScore);
		}
	}
	Slider->SetIsEnabled(false);
	if (!ensure(EndGameMenuClass != nullptr))return;
	auto EndGameMenu = CreateWidget<UEndGameMenu>(this, EndGameMenuClass);
	if (!ensure(EndGameMenu != nullptr))return;
	EndGameMenu->Setup();
	EndGameMenu->SetMenuInterface(this);
}
void UUniverseGameInstance::saveHighScore_Implementation(float score){}

void UUniverseGameInstance::Start() {
	bGameOver = false;
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel("/Game/Maps/Universe", ETravelType::TRAVEL_Absolute);
}
void UUniverseGameInstance::Quit() {
	auto* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;
	playerController->ConsoleCommand("quit");
}
void UUniverseGameInstance::Highscore() {

}
