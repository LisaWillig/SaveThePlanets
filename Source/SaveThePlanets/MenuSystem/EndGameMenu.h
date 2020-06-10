// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "EndGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEPLANETS_API UEndGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextScore;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HighScore;

	float High = 0;
	float Score = 0;

	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Start();
	UFUNCTION()
	void TravelMainMenu();

};
