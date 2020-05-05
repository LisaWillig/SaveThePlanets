// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "Opponents.h"
#include "UniverseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UUniverseGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
    
    UUniverseGameInstance();

    UFUNCTION(BlueprintCallable)
    void LoadSlider();

    void SetTime(float NewTime);
    float GetTime();

    void Start();
    void Quit();
    void Highscore();

    UFUNCTION(BlueprintCallable)
    void LoadMainMenu();

    UFUNCTION(BlueprintCallable)
    void TravelMainMenu();

    UFUNCTION(BlueprintCallable)
    void LoadHighscoreMenu();

    UFUNCTION(BlueprintCallable)
    void LoadPauseMenu();

    UFUNCTION(BlueprintCallable)
    void TravelHighscoreMenu();

    UFUNCTION(BlueprintCallable)
    void GameOver();

    //AOpponents OpponentSpawner;

    bool bGameOver = false;

private:
    float TimeValue;

    TSubclassOf<class UUserWidget> MainMenuClass;
    TSubclassOf<class UUserWidget> SliderClass;
    TSubclassOf<class UUserWidget> HighscoreClass;
    TSubclassOf<class UUserWidget> PauseMenuClass; 
    TSubclassOf<class UUserWidget> EndGameMenuClass;

    class UMenuWidget* Slider;
    class UMenuWidget* MainMenu;


};
